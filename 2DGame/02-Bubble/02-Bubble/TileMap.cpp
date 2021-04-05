#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TileMap.h"


using namespace std;


TileMap *TileMap::createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	TileMap *map = new TileMap(levelFile, minCoords, program);
	
	return map;
}


TileMap::TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	loadLevel(levelFile);
	prepareArrays(minCoords, program);
}

TileMap::~TileMap()
{
	if (map != NULL) {
		delete map;
		map = nullptr;
	}

	if (characMap != NULL) {
		delete characMap;
		characMap = nullptr;
	}
		
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

bool TileMap::loadLevel(const string &levelFile)
{
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;
	char tile;

	fin.open(levelFile.c_str());
	if (!fin.is_open()) return false;
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

	string accum = "";
	map = new int[mapSize.x * mapSize.y];
	characMap = new int[mapSize.x * mapSize.y];

	for (int j = 0; j < mapSize.y; j++) {
		for (int i = 0; i < mapSize.x; i++) {
			fin.get(tile);
			accum = " ";
			while (tile != ',') {
				accum += tile;
				fin.get(tile);
			}
			int id = stoi(accum);
			map[j * mapSize.x + i] = id + 1;
			characMap[j * mapSize.x + i] = 1;
		}
		fin.get(tile);
#ifndef _WIN32
		fin.get(tile);
#endif
	}
	fin.close();

	return true;
}

void TileMap::prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program)
{
	int tile, nTiles = 0;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> vertices;
	
	halfTexel = glm::vec2(0.5f / tilesheet.width(), 0.5f / tilesheet.height());
	for(int j=0; j<mapSize.y; j++)
	{
		for(int i=0; i<mapSize.x; i++)
		{
			tile = map[j * mapSize.x + i];
			if(tile != 0)
			{
				// Non-empty tile
				nTiles++;
				posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize);
				texCoordTile[0] = glm::vec2(float((tile-1)% tilesheetSize.x) / tilesheetSize.x, float((tile-1)/ tilesheetSize.x) / tilesheetSize.y);
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
	posLocation = program.bindVertexAttribute("position", 2, 4*sizeof(float), 0);
	texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4*sizeof(float), (void *)(2*sizeof(float)));
}

// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.

bool TileMap::collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0, y1;

	x = pos.x / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++)
	{
		if (map[y * mapSize.x + x] == 6 || map[y * mapSize.x + x] == 198 || map[y * mapSize.x + x] == 199 || map[y * mapSize.x + x] == 200 || map[y * mapSize.x + x] == 242 || map[y * mapSize.x + x] == 146 ||
			map[y * mapSize.x + x] == 147 || map[y * mapSize.x + x] == 215 || map[y * mapSize.x + x] == 130 || map[y * mapSize.x + x] == 258 || map[y * mapSize.x + x] == 22 || map[y * mapSize.x + x] == 262 || map[y * mapSize.x + x] == 263
			|| map[y * mapSize.x + x] == 266 || map[y * mapSize.x + x] == 170 || map[y * mapSize.x + x] == 171 || map[y * mapSize.x + x] == 30
			|| map[y * mapSize.x + x] == 231 || map[y * mapSize.x + x] == 38
			|| map[y * mapSize.x + x] == 233 || map[y * mapSize.x + x] == 235 || map[y * mapSize.x + x] == 187 || map[y * mapSize.x + x] == 185 || map[y * mapSize.x + x] == 45)
			return true;
	}

	return false;
}

bool TileMap::collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0, y1;

	x = (pos.x + size.x - 1) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++)
	{
		if (map[y * mapSize.x + x] == 6 || map[y * mapSize.x + x] == 198 || map[y * mapSize.x + x] == 199 || map[y * mapSize.x + x] == 200 || map[y * mapSize.x + x] == 242 || map[y * mapSize.x + x] == 146 ||
			map[y * mapSize.x + x] == 147 || map[y * mapSize.x + x] == 214 || map[y * mapSize.x + x] == 130 || map[y * mapSize.x + x] == 258 || map[y * mapSize.x + x] == 22 || map[y * mapSize.x + x] == 262 || map[y * mapSize.x + x] == 263
			|| map[y * mapSize.x + x] == 266 || map[y * mapSize.x + x] == 170 || map[y * mapSize.x + x] == 171 || map[y * mapSize.x + x] == 30
			|| map[y * mapSize.x + x] == 231 || map[y * mapSize.x + x] == 38
			|| map[y * mapSize.x + x] == 233 || map[y * mapSize.x + x] == 235 || map[y * mapSize.x + x] == 187 || map[y * mapSize.x + x] == 185 || map[y * mapSize.x + x] == 45)
			return true;
	}

	return false;
}

bool TileMap::collisionMoveStairsLeft(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0, y1;
	x = (pos.x + 2 * size.x / 3 - 1) / tileSize;

	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++)
	{
		if (map[y * mapSize.x + x] != 3 && map[y * mapSize.x + x] != 19 && map[y * mapSize.x + x] != 27 && map[y * mapSize.x + x] != 35
			&& map[y * mapSize.x + x] != 43)
			return true;
	}

	return false;
}

bool TileMap::collisionMoveStairsRight(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0, y1;
	x = (pos.x) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++)
	{
		if (map[y * mapSize.x + x] != 3 && map[y * mapSize.x + x] != 337 && map[y * mapSize.x + x] != 19 && map[y * mapSize.x + x] != 27
			&& map[y * mapSize.x + x] != 35 && map[y * mapSize.x + x] != 43)
			return true;
	}

	return false;
}

bool TileMap::collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const
{
	int x0, x1, y;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y - 1) / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		if (map[y * mapSize.x + x] == 290 || map[y * mapSize.x + x] == 193 || map[y * mapSize.x + x] == 194 || map[y * mapSize.x + x] == 195 || map[y * mapSize.x + x] == 198 || map[y * mapSize.x + x] == 150 || map[y * mapSize.x + x] == 198 ||
			map[y * mapSize.x + x] == 146 || map[y * mapSize.x + x] == 214 || map[y * mapSize.x + x] == 166 || map[y * mapSize.x + x] == 215 || map[y * mapSize.x + x] == 147 || map[y * mapSize.x + x] == 6 || map[y * mapSize.x + x] == 306 ||
			map[y * mapSize.x + x] == 163 || map[y * mapSize.x + x] == 162 || map[y * mapSize.x + x] == 22 || map[y * mapSize.x + x] == 314 || map[y * mapSize.x + x] == 171 || map[y * mapSize.x + x] == 170 || map[y * mapSize.x + x] == 30
			|| map[y * mapSize.x + x] == 273 || map[y * mapSize.x + x] == 225 || map[y * mapSize.x + x] == 226 || map[y * mapSize.x + x] == 38
			|| map[y * mapSize.x + x] == 186 || map[y * mapSize.x + x] == 187 || map[y * mapSize.x + x] == 185 || map[y * mapSize.x + x] == 236 || map[y * mapSize.x + x] == 46)
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

bool TileMap::roofMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const
{
	int x0, x1, y;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y - 1) / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		if (map[y * mapSize.x + x] == 290 || map[y * mapSize.x + x] == 193 || map[y * mapSize.x + x] == 194 || map[y * mapSize.x + x] == 195 || map[y * mapSize.x + x] == 198 || map[y * mapSize.x + x] == 150 || map[y * mapSize.x + x] == 198 ||
			map[y * mapSize.x + x] == 146 || map[y * mapSize.x + x] == 214 || map[y * mapSize.x + x] == 166 || map[y * mapSize.x + x] == 215 || map[y * mapSize.x + x] == 147 || map[y * mapSize.x + x] == 6 || map[y * mapSize.x + x] == 306 ||
			map[y * mapSize.x + x] == 163 || map[y * mapSize.x + x] == 162 || map[y * mapSize.x + x] == 22 || map[y * mapSize.x + x] == 314 || map[y * mapSize.x + x] == 171 || map[y * mapSize.x + x] == 170 || map[y * mapSize.x + x] == 30
			|| map[y * mapSize.x + x] == 273 || map[y * mapSize.x + x] == 225 || map[y * mapSize.x + x] == 226 || map[y * mapSize.x + x] == 38
			|| map[y * mapSize.x + x] == 186 || map[y * mapSize.x + x] == 187 || map[y * mapSize.x + x] == 185 || map[y * mapSize.x + x] == 236 || map[y * mapSize.x + x] == 46)
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

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y) / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		if (map[y * mapSize.x + x] == 242 || map[y * mapSize.x + x] == 194 || map[y * mapSize.x + x] == 258 || map[y * mapSize.x + x] == 262 || map[y * mapSize.x + x] == 263 || map[y * mapSize.x + x] == 312
			|| map[y * mapSize.x + x] == 210 || map[y * mapSize.x + x] == 266 || map[y * mapSize.x + x] == 218 || map[y * mapSize.x + x] == 270 || map[y * mapSize.x + x] == 271 || map[y * mapSize.x + x] == 320
			|| map[y * mapSize.x + x] == 274 || map[y * mapSize.x + x] == 232 || map[y * mapSize.x + x] == 38 || map[y * mapSize.x + x] == 226
			|| map[y * mapSize.x + x] == 239 || map[y * mapSize.x + x] == 381 || map[y * mapSize.x + x] == 233 || map[y * mapSize.x + x] == 234 || map[y * mapSize.x + x] == 235)
			return true;
	}

	return false;
}

bool TileMap::collisionFall(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const
{
	int x0, x1, y, y1;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y ) / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		if (map[y * mapSize.x + x] == 337) {
			return true;
		}
	}
	return false;
}

bool TileMap::isStairs(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x0, x1, y;

	x0 = (pos.x + size.x / 2 - 1) / tileSize;
	x1 = (pos.x + 2 * size.x / 3 - 1) / tileSize;
	y = (pos.y + size.y - 1) / tileSize;
	if (map[y * mapSize.x + x0] == 3 || map[y * mapSize.x + x0] == 19 || map[y * mapSize.x + x0] == 27 || map[y * mapSize.x + x0] == 35
		|| map[y * mapSize.x + x0] == 43)
		return true;


	return false;
}

bool TileMap::checkPlayerLeft(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0, y1;

	x = (pos.x - size.x) / tileSize;
	y0 = (pos.y - size.y) / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++)
	{
		if (characMap[y * mapSize.x + x] == 2)
			return true;
	}

	return false;
}

bool TileMap::checkPlayerRight(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0, y1;

	x = (pos.x + size.x) / tileSize;
	y0 = (pos.y - size.y) / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++)
	{
		if (characMap[y * mapSize.x + x] == 2)
			return true;
	}

	return false;
}

void TileMap::updatePositionTile(const glm::ivec2& posAc, const glm::ivec2& posAnt, const glm::ivec2& size, int id) const
{
	int x, y, x1, y1;

	x = posAc.x / tileSize;
	y = posAc.y / tileSize;
	x1 = posAnt.x / tileSize;
	y1 = posAnt.y / tileSize;
	for (int j = 0; j < mapSize.y; j++) {
		for (int i = 0; i < mapSize.x; i++) {
			if (characMap[j * mapSize.x + i] == id)
				characMap[j * mapSize.x + i] = 1;
		}
	}
	characMap[y * mapSize.x + x] = id;
}

void TileMap::updatePositionFakeRoof(const glm::ivec2& posAc, const glm::ivec2& posAnt, const glm::ivec2& size, int id) const
{
	int x, y, x1, y1;

	x = posAc.x / tileSize;
	y = posAc.y / tileSize;
	x1 = posAnt.x / tileSize;
	y1 = posAnt.y / tileSize;
	for (int j = 0; j < mapSize.y; j++) {
		for (int i = 0; i < mapSize.x; i++) {
			if (characMap[j * mapSize.x + i] == id)
				characMap[j * mapSize.x + i] = 1;
		}
	}
	characMap[y * mapSize.x + x] = id;
	characMap[y * mapSize.x + (x + 1)] = id;
	characMap[(y + 1) * mapSize.x + x] = id;
	characMap[(y + 1) * mapSize.x + (x + 1)] = id;
}

bool TileMap::checkDamage(const glm::ivec2& pos, const glm::ivec2& size, bool helmet) const
{
	int x, y0, y1;

	x = (pos.x + size.x - 1) / tileSize;
	y0 = pos.y / tileSize;
	y1 = ((pos.y + size.y - 1) / tileSize);
	for (int y = y0; y <= y1; y++)
	{
		if (helmet) {
			if (characMap[y * mapSize.x + x] != 2 && characMap[y * mapSize.x + x] != 1 && characMap[y * mapSize.x + x] != 70 && characMap[y * mapSize.x + x] != 50 && characMap[y * mapSize.x + x] != 40 && characMap[y * mapSize.x + x] != 41 && characMap[y * mapSize.x + x] != 42 && characMap[y * mapSize.x + x] != 43 && characMap[y * mapSize.x + x] != 90)
				return true;
		}
		if (!helmet) {
			if (characMap[y * mapSize.x + x] != 2 && characMap[y * mapSize.x + x] != 1 && characMap[y * mapSize.x + x] != 70 && characMap[y * mapSize.x + x] != 50 && characMap[y * mapSize.x + x] != 90)
				return true;
		}
	}
	return false;
}

bool TileMap::checkPlayerDown(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0;

	x = pos.x / tileSize;
	y0 = (pos.y / tileSize) + 1;
	for (int y = y0; y <= (mapSize.y - y0); y++)
	{
		if (characMap[y * mapSize.x + x] == 2)
			return true;
		else if (map[y * mapSize.x + x] != 337 && map[y * mapSize.x + x] != 242) return false;
	}
	return false;
}

bool TileMap::checkIfPlayer(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0, y1;

	x = (pos.x + size.x) / tileSize;
	y0 = (pos.y / tileSize) - 1;
	y1 = (pos.y / tileSize);

	for (int y = y0; y <= y1; y++)
	{
		if (characMap[y * mapSize.x + x] == 2)
			return true;
	}
	return false;
}

void TileMap::clearPosition(int id) const
{
	for (int j = 0; j < mapSize.y; j++) {
		for (int i = 0; i < mapSize.x; i++) {
			if (characMap[j * mapSize.x + i] == id)
				characMap[j * mapSize.x + i] = 1;
		}
	}
}

bool TileMap::checkIfKey(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0;

	x = (pos.x - 1) / tileSize;
	y0 = (pos.y / tileSize) + 1;
	if (characMap[y0 * mapSize.x + x] == 50) return true;
	return false;
}

bool TileMap::checkIfChip(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0;

	x = (pos.x - 1) / tileSize;
	y0 = (pos.y / tileSize) + 1;
	if (characMap[y0 * mapSize.x + x] == 20) return true;
	return false;
}

void TileMap::openDoor(const glm::ivec2& pos) const
{
	int x, y, y1;

	x = pos.x / tileSize;
	y = pos.y / tileSize;
	y1 = (pos.y / tileSize) + 1;
	map[y * mapSize.x + x] = 337;
	map[y1 * mapSize.x + x] = 337;
}


bool TileMap::checkEnemyBulletDamage(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x0, x1, y0, y1;

	x0 = (pos.x - size.x + 16) / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y0 = (pos.y - size.y) / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++) {
		for (int x = x0; x <= x1; x++)
		{
			if (characMap[y * mapSize.x + x] == 3 || characMap[y * mapSize.x + x] == 4 || characMap[y * mapSize.x + x] == 5 || characMap[y * mapSize.x + x] == 6 || characMap[y * mapSize.x + x] == 7 || characMap[y * mapSize.x + x] == 8 || characMap[y * mapSize.x + x] == 9 || characMap[y * mapSize.x + x] == 10 || characMap[y * mapSize.x + x] == 11 || characMap[y * mapSize.x + x] == 12)
				return true;
		}
	}
	return false;
}