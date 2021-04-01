#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TileMap.h"
#include <crtdbg.h>


using namespace std;


TileMap* TileMap::createTileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program)
{
	TileMap* map = new TileMap(levelFile, minCoords, program);

	return map;
}


TileMap::TileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program)
{
	loadLevel(levelFile);
	prepareArrays(minCoords, program);
}

TileMap::~TileMap()
{
	if (map != NULL)
		delete map;
}


void TileMap::render() const
{
	glEnable(GL_TEXTURE_2D);
	tilesheet.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6 * mapSize.x * mapSize.y);
	glDisable(GL_TEXTURE_2D);
}

void TileMap::free()
{
	glDeleteBuffers(1, &vbo);
}

bool TileMap::loadLevel(const string& levelFile)
{
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;
	char row, column;
	int irow, icolumn, coords;

	fin.open(levelFile.c_str());
	if (!fin.is_open())
		return false;
	getline(fin, line);
	if (line.compare(0, 7, "TILEMAP") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);
	sstream.str(line);
	sstream >> tileSize >> blockSize;
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetFile;
	tilesheet.loadFromFile(tilesheetFile, TEXTURE_PIXEL_FORMAT_RGBA);
	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
	tilesheet.setMinFilter(GL_NEAREST);
	tilesheet.setMagFilter(GL_NEAREST);
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetSize.x >> tilesheetSize.y;
	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);

	map = new int[mapSize.x * mapSize.y];
	for (int j = 0; j < mapSize.y; j++)
	{
		for (int i = 0; i < mapSize.x; i++)
		{
			fin.get(row);
			irow = row - 65;
			fin.get(column);
			icolumn = column - 96;
			coords = irow * tilesheetSize.x + icolumn;
			map[j * mapSize.x + i] = coords;
			/*if (tile == ' ')
			map[j*mapSize.x + i] = 0;
			else
			map[j*mapSize.x + i] = tile - 96;
			*/
		}
		fin.get(row);
#ifndef _WIN32
		fin.get(row);
#endif
	}
	fin.close();

	return true;
}

void TileMap::prepareArrays(const glm::vec2& minCoords, ShaderProgram& program)
{
	int tile, nTiles = 0;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> vertices;

	halfTexel = glm::vec2(0.5f / tilesheet.width(), 0.5f / tilesheet.height());
	for (int j = 0; j < mapSize.y; j++)
	{
		for (int i = 0; i < mapSize.x; i++)
		{
			tile = map[j * mapSize.x + i];
			if (tile != 0)
			{
				// Non-empty tile
				nTiles++;
				posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize);
				texCoordTile[0] = glm::vec2(float((tile - 1) % 16) / tilesheetSize.x, float((tile - 1) / 16) / tilesheetSize.y);
				texCoordTile[1] = texCoordTile[0] + tileTexSize;
				//texCoordTile[0] += halfTexel;
				texCoordTile[1] -= halfTexel;
				// First triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				// Second triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
			}
		}
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.

bool TileMap::collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0, y1;
	x = (pos.x + 7) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++) {
		if ((map[y * mapSize.x + x] >= 49 && map[y * mapSize.x + x] <= 56) ||
			(map[y * mapSize.x + x] >= 65 && map[y * mapSize.x + x] <= 70) ||
			map[y * mapSize.x + x] == 14   //Am
			) {
			return true;
		}
	}
	return false;
}

bool TileMap::collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0, y1;
	x = (pos.x + size.x + 9) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++) {
		if ((map[y * mapSize.x + x] >= 49 && map[y * mapSize.x + x] <= 56) ||
			(map[y * mapSize.x + x] >= 65 && map[y * mapSize.x + x] <= 70) ||
			map[y * mapSize.x + x] == 13   //Am
			)
			return true;
	}
	return false;
}

bool TileMap::esticSobreTerra(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x0, x1, y;

	x0 = (pos.x + 8) / tileSize;
	x1 = (pos.x + 22) / tileSize;
	y = (pos.y + 16) / tileSize;
	for (int x = x0; x <= x1; x++) {
		if (map[y * mapSize.x + x] >= 1 && map[y * mapSize.x + x] <= 37 && map[y * mapSize.x + x] != 32)
			return true;
	}
	return false;
}


bool TileMap::climbingPlant(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y;
	x = (pos.x + 16) / tileSize;
	y = (pos.y + 16) / tileSize;
	if (map[y * mapSize.x + x] == 31 || //Bo
		map[y * mapSize.x + x] == 32	//Bp
		) return true;
	else return false;
}

bool TileMap::descendingPlant(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y, y1;
	x = (pos.x + 16) / tileSize;
	y = (pos.y + 16) / tileSize;
	y1 = (pos.y + 32) / tileSize;
	if (map[y1 * mapSize.x + x] == 31 && //Bo
		(map[y * mapSize.x + x] == 1	||	map[y1 * mapSize.x + x] == 7) // Aa o Ag
		) return true;
	else return false;
}

bool TileMap::finalPartOfPlantClimbing(const glm::ivec2& pos, const glm::ivec2& size, int* posX) const
{
	int x, y, y1;
	x = (pos.x + 16) / tileSize;
	y = (pos.y + 16) / tileSize;
	y1 = (pos.y) / tileSize;
	if (map[y * mapSize.x + x] == 31 &&  //Bo
		(map[y1 * mapSize.x + x] == 1 || map[y1 * mapSize.x + x] == 2	|| map[y1 * mapSize.x + x] == 26 || map[y1 * mapSize.x + x ] == 27 || map[y1 * mapSize.x + x] == 7 ) // Aa  o Ab o Ag o Bj o Bk
		) {
		*posX = x*tileSize - 8;
		return true;
	}
	else return false;
}

bool TileMap::finalPartOfPlantDescending(const glm::ivec2& pos, const glm::ivec2& size, int* posX) const
{
	int x, y;
	x = (pos.x + 16) / tileSize;
	y = (pos.y + 16) / tileSize;
	if (map[y * mapSize.x + x] == 2)	 // Ab
	{
		*posX = x*tileSize - 8;
		return true;
	}
	else return false;
}

bool TileMap::collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const
{
	int x0, x1, y;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y - 1) / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		if (map[y * mapSize.x + x] != 0)
		{
			if (*posY - tileSize * y + size.y <= 4)
			{
				*posY = tileSize * y - size.y;
				return true;
			}
		}
	}

	return false;
}

bool TileMap::collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x0, x1, y;

	x0 = (pos.x + 8) / tileSize;
	x1 = (pos.x + 22) / tileSize;
	y = pos.y / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		if ((map[y * mapSize.x + x] >= 49 && map[y * mapSize.x + x] <= 56) ||
			(map[y * mapSize.x + x] >= 65 && map[y * mapSize.x + x] <= 70))
		{
			return true;
		}
	}

	return false;
}

bool TileMap::nextScreen(const glm::ivec2 & pos, const glm::ivec2 & size) const
{
	int x, y0, y1;
	x = (pos.x + size.x - 12) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++) {
		if (map[y * mapSize.x + x] == 222 || map[y * mapSize.x + x] == 254)
			return true;
	}
	return false;
}

bool TileMap::prevScreen(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0, y1;
	x = (pos.x + 12) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++) {
		if (map[y * mapSize.x + x] == 256 || map[y * mapSize.x + x] == 255) {
			return true;
		}
	}
	return false;
}

bool TileMap::skullsobreterra(const glm::ivec2 & pos, const glm::ivec2 & size, bool side) const
{
	int x0 = 0, x1 = 0, y;
	if (side) { //TRUE = moving right | FALSE = moving left
		x0 = (pos.x + 30) / tileSize;
		x1 = (pos.x + 38) / tileSize;
	}
	else
	{
		x0 = (pos.x - 8) / tileSize;
		x1 = (pos.x ) / tileSize;
	}
	y = (pos.y + 16) / tileSize;
	for (int x = x0; x <= x1; x++) {
		if ((map[y * mapSize.x + x] == 1 ||
			 map[y * mapSize.x + x] == 2) || 
			(map[y * mapSize.x + x] >= 7 && map[y * mapSize.x + x] <= 37 && map[y * mapSize.x + x] != 32))
			return true;
	}
	return false;
}


bool TileMap::portal(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y;
	x = (pos.x + 16) / tileSize;
	y = (pos.y) / tileSize;
	if (map[y * mapSize.x + x] >= 240 && //Pa
		map[y * mapSize.x + x] <= 250	//Pb
		) return true;
	else return false;
}

int TileMap::quinPortal(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y;
	x = (pos.x + 16) / tileSize;
	y = (pos.y) / tileSize;
	if (map[y * mapSize.x + x] == 241) return 1;
	else if (map[y * mapSize.x + x] == 242) return 2;
	else if (map[y * mapSize.x + x] == 243) return 3;
	else if (map[y * mapSize.x + x] == 244) return 4;
	else if (map[y * mapSize.x + x] == 245) return 5;
	else if (map[y * mapSize.x + x] == 246) return 6;
	else if (map[y * mapSize.x + x] == 247) return 7;
	else if (map[y * mapSize.x + x] == 248) return 8;
	else if (map[y * mapSize.x + x] == 249) return 9;
	else if (map[y * mapSize.x + x] == 250) return 10;
	else return 0;
}