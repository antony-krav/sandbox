#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include "pugiXML/pugixml.hpp"	// XML ������

struct Layer
{
	short opacity;							// �������������� ����
	std::vector<sf::Sprite> tiles;			// ������ ������
};

struct Object
{
	int GetPropertyInt(std::string name);				// ����� �������� ������� � ����� ������ � int
	float GetPropertyFloat(std::string name);			// ����� �������� ������� � ����� ������ � float
	std::string GetPropertyString(std::string name);	// ����� �������� ������� � ����� ������ � std::string

	std::string name;									// ��� ��������
	std::string type;									// ��� ��������
	sf::Rect<float> rect;								// ��� Rect � �������� ����������
	std::map<std::string, std::string> properties;		// ������������ ������, ���� - ��������� ���, �������� - ���������
	sf::Sprite sprite;
};

class Level :public sf::Transformable, public sf::Drawable
{
public:
	bool LoadFromFile(std::string);									// �������� �����, �������� - ���� �� �����. ���������� "false" ��� �������
	Object GetObject(std::string);									// ���������� ������ ������ � ��������� ������
	std::vector<Object> GetObjects(std::string);					// ���������� ������ ���� �������� � ��������� ������
	std::vector<Object> GetAllObjects();							// ���������� ������ ���� ��������
	sf::Vector2i GetTileSize();										// ���������� ������ �����
private:
	short mapWidth, mapHeight;										// ������ � ������ ����� � ������
	short tileWidth, tileHeight;									// ������ � ������ ������ � ��������
	short firstGid;													// Gid ������� �����
	sf::Texture tilesetTexture;										// �������� ��������
	std::vector<Object> objects;									// ������ ��������
	std::vector<Layer> layers;										// ������ �����

	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;	// ������������ ��� �����
};

#endif // LEVEL_HPP