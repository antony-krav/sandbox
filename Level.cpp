#include "Level.hpp"

int Object::GetPropertyInt(std::string name)
{
	return atoi(properties[name].c_str());
}
float Object::GetPropertyFloat(std::string name)
{
	return strtod(properties[name].c_str(), NULL);
}
std::string Object::GetPropertyString(std::string name)
{
	return properties[name];
}

bool Level::LoadFromFile(std::string pathToMap)
{
	pugi::xml_document map;

	if (!map.load_file(pathToMap.c_str()))
	{
		std::cerr << "Error loading map file " << pathToMap << "!" << std::endl;
		return false;
	}

	pugi::xml_node* mapTag = &map.child("map");

	mapWidth = mapTag->attribute("width").as_int();
	mapHeight = mapTag->attribute("height").as_int();
	tileWidth = mapTag->attribute("tilewidth").as_int();
	tileHeight = mapTag->attribute("tileheight").as_int();

	pugi::xml_node* tilesetTag = &mapTag->child("tileset");
	firstGid = tilesetTag->attribute("firstgid").as_int();
	
	short spacing = tilesetTag->attribute("spacing").as_int();
	short margin = tilesetTag->attribute("margin").as_int();

	pugi::xml_node* imageTag = &tilesetTag->child("image");
	std::string pathToTilesetImage = imageTag->attribute("source").as_string();

	sf::Image tilesetImage;
	if (!tilesetImage.loadFromFile(pathToTilesetImage))
	{
		std::cerr << "Error loading tileset image!" << std::endl;
		return false;
	}

	tilesetTexture.loadFromImage(tilesetImage);

	short columns = (tilesetTexture.getSize().x - margin) / (tileWidth + spacing); /////////////////////////////////////////////////
	short rows = (tilesetTexture.getSize().y - margin) / (tileHeight + spacing);

	std::vector<sf::Rect<int>> subRects;

	for (int x = 0; x < rows; ++x)
		for (int y = 0; y < columns; ++y)
		{
			sf::Rect<int> tile;
			tile.top = x * (tileHeight + spacing) + margin;
			tile.height = tileHeight;
			tile.left = y * (tileWidth + spacing) + margin;
			tile.width = tileWidth;

			subRects.push_back(tile);
		}

	//////////////////
	// layers
	//////////////////

	pugi::xml_node* layerTag = &mapTag->child("layer");
	while (*layerTag)
	{
		Layer layer;

		if (layerTag->attribute("opacity").as_bool())
		{
			layer.opacity = layerTag->attribute("opacity").as_float();
		}
		else
			layer.opacity = 255;

		pugi::xml_node* layerDataTag = &layerTag->child("data");
		pugi::xml_node* tileTag = &layerDataTag->child("tile");

		short x = 0;
		short y = 0;

		while (*tileTag)
		{
			int tileGid = tileTag->attribute("gid").as_int();
			int subRectToUse = tileGid - firstGid;

			if (subRectToUse >= 0)
			{
				sf::Sprite sprite;
				sprite.setTexture(tilesetTexture);
				sprite.setTextureRect(subRects[subRectToUse]);
				sprite.setPosition(x * tileWidth, y * tileHeight);
				sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

				layer.tiles.push_back(sprite);
			}

			tileTag = &tileTag->next_sibling("tile");
			++x;
			if (x >= mapWidth)
			{
				x = 0;
				++y;
				if (y >= mapHeight)
					y = 0;
			}
		}
		layers.push_back(layer);
		layerTag = &layerTag->next_sibling("layer");
	}

	//////////////////
	// objects
	//////////////////

	if (mapTag->child("objectgroup") != NULL)
	{
		pugi::xml_node* objectGroupTag = &mapTag->child("objectgroup");
		while (*objectGroupTag)
		{
			pugi::xml_node* objectTag = &objectGroupTag->child("object");
			while (*objectTag)
			{
				std::string objectName;
				if (objectTag->attribute("name").as_bool())
				{
					objectName = objectTag->attribute("name").as_string();
				}
				int x = objectTag->attribute("x").as_int();
				int y = objectTag->attribute("y").as_int();

				int width = objectTag->attribute("width").as_int();
				int height = objectTag->attribute("height").as_int();

				sf::Sprite sprite;
				sprite.setTexture(tilesetTexture);
				sprite.setTextureRect(sf::Rect<int>(0, 0, 0, 0));
				sprite.setPosition(x, y);

				Object object;
				object.name = objectName;
				object.sprite = sprite;

				sf::Rect<float> objectRect;
				objectRect.top = y;
				objectRect.left = x;
				objectRect.height = height;
				objectRect.width = width;
				object.rect = objectRect;

				objects.push_back(object);
				objectTag = &objectTag->next_sibling("object");
			}
			objectGroupTag = &objectGroupTag->next_sibling("objectgroup");
		}
	}
	else std::cout << "No object layer found..." << std::endl;
	return true;
}
Object Level::GetObject(std::string name)
{
	for (int i = 0; i < objects.size(); i++)
		if (objects[i].name == name)
			return objects[i];
}
std::vector<Object> Level::GetObjects(std::string name)
{
	std::vector<Object> vec;
	for (int i = 0; i < objects.size(); i++)
		if (objects[i].name == name)
			vec.push_back(objects[i]);
	return vec;
}
std::vector<Object> Level::GetAllObjects()
{
	return objects;
};
sf::Vector2i Level::GetTileSize()
{
	return sf::Vector2i(tileWidth, tileHeight);
}
void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	for (int layer = 0; layer < layers.size(); layer++)
		for (int tile = 0; tile < layers[layer].tiles.size(); tile++)
			target.draw(layers[layer].tiles[tile], states);
}