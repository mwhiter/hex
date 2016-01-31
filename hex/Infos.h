#pragma once

#include "enums.h"
#include "base.h"

namespace mandr {

	class Infos
	{
	public:
		Infos(std::string type);
		~Infos();

		uint getID() const;
		std::string getType() const;
	private:
		static uint idCount;
		uint m_ID;
		std::string m_Type;
	};

	class TerrainInfo : public Infos {
	public:
		TerrainInfo();
		TerrainInfo(std::string type, int moveCost, int texture, TerrainType terrain);
	
		int getMovementCost() const;
		sf::Texture* getTexture() const;
		TerrainType getTerrainType() const;
	private:
		int m_MovementCost;
		sf::Texture* m_pTexture;
		TerrainType m_TerrainType;
	};

}