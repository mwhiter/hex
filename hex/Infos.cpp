#include "PCH.h"

namespace mandr {

	uint Infos::idCount = 0;

	Infos::Infos(std::string type) :
		m_ID(idCount++),
		m_Type(type)
	{
	}


	Infos::~Infos()
	{
	}

	uint Infos::getID() const {
		return m_ID;
	}

	std::string Infos::getType() const {
		return m_Type;
	}

	TerrainInfo::TerrainInfo() :
		Infos(""),
		m_MovementCost(0),
		m_pTexture(),
		m_TerrainType(NO_TERRAIN_TYPE)
	{
	}

	TerrainInfo::TerrainInfo(std::string type, int moveCost, int texture, TerrainType terrain) :
		Infos(type),
		m_MovementCost(moveCost),
		m_pTexture(GAME.getTexture(texture)),
		m_TerrainType(terrain)
	{
	}

	int TerrainInfo::getMovementCost() const {
		return m_MovementCost;
	}

	sf::Texture* TerrainInfo::getTexture() const {
		return m_pTexture;
	}

	TerrainType TerrainInfo::getTerrainType() const {
		return m_TerrainType;
	}

}