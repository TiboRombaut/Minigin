#include "Coily.h"

#include <GameTime.h>
#include <memory>
#include <GameObject.h>

Coily::Coily(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> field, std::vector<std::shared_ptr<QBertComponent>>& Qberts,
	float timeItTakesToMove, std::shared_ptr<dae::TextureComponent> textureComp)
	:AIComponent(timeItTakesToMove,textureComp)
	,m_CoilyGameObject(pObject)
	, m_pQBerts(Qberts)
{
	m_pCommandMoveLeftUp = new MoveLeftUpCommand(pObject, field, "../Data/BackGroundTileYellow.png");
	m_pCommandMoveRightUp = new MoveRightUpCommand(pObject, field, "../Data/BackGroundTileYellow.png");
	m_pCommandMoveRightDown = new MoveRightDownCommand(pObject, field, "../Data/BackGroundTileYellow.png");
	m_pCommandMoveLeftDown = new MoveLeftDownCommand(pObject, field, "../Data/BackGroundTileYellow.png");
}

Coily::~Coily()
{
	delete m_pCommandMoveLeftUp;
	delete m_pCommandMoveRightUp;
	delete m_pCommandMoveRightDown;
	delete m_pCommandMoveLeftDown;
}

bool Coily::GetIsDead()const
{
	return m_IsDead;
}

void Coily::SetIsDead(bool isDead)
{
	m_IsDead = isDead;
}

void Coily::Update()
{
	m_CurrentTime += GameTime::GetInstance().GetDeltaTime();

	if (m_NeedsToMove)
	{
		UpdateMovement();
	}

	if (GetCanMove())
	{
		if (IsEgg)
		{
			int whatMovement = rand() % 2;
			switch (whatMovement)
			{
			case 0:
				//move left
				m_pCommandMoveLeftDown->Execute();
				break;
			case 1:
				//move right
				m_pCommandMoveRightDown->Execute();
				break;
			default:
				//nothing
				break;
			}

			if (m_QBertFieldData.Row == 6)
			{
				std::cout << "reachedBottom\n";
				IsEgg = false;
				//change texture
				m_CoilyGameObject->GetComponent<dae::TextureComponent>()->SetTexture("../Data/Coily.png");
				// //startPathfinding
				//GetGameObject()->SetIsActive(false);
			}
		}
		else
		{

			//do pathfinding
			//std::cout << "pathfinding\n";
			//std::vector<PossibleMovement> whatMovementsArePossible;
			////first of all try to find possible movements.
			//if (m_QBertFieldData.Column == 0)
			//{
			//	//can't move leftTop
			//	if (m_QBertFieldData.Row == 0)
			//	{
			//		//can move left down , right down
			//		whatMovementsArePossible.push_back(PossibleMovement::LeftDown);
			//		whatMovementsArePossible.push_back(PossibleMovement::RightDown);
			//	}
			//	else if (m_QBertFieldData.Row == 6)
			//	{
			//		// can move right up
			//		whatMovementsArePossible.push_back(PossibleMovement::RightUp);
			//	}
			//	else
			//	{
			//		// can move right up, right down , left down
			//		whatMovementsArePossible.push_back(PossibleMovement::RightUp);
			//		whatMovementsArePossible.push_back(PossibleMovement::RightDown);
			//		whatMovementsArePossible.push_back(PossibleMovement::LeftDown);
			//	}
			//}
			//else if (m_QBertFieldData.Column == m_QBertFieldData.Row)
			//{
			//	//if the currentColumn we are on == the current row we are on => he is on the last column of the row

			//	//can't move rightTop
			//	if (m_QBertFieldData.Row == 0)
			//	{
			//		//can move left down , right down
			//		whatMovementsArePossible.push_back(PossibleMovement::LeftDown);
			//		whatMovementsArePossible.push_back(PossibleMovement::RightDown);
			//	}
			//	else if (m_QBertFieldData.Row == 6)
			//	{
			//		// can move left up
			//		whatMovementsArePossible.push_back(PossibleMovement::LeftUp);
			//	}
			//	else
			//	{
			//		// can move left up, right down , left down
			//		whatMovementsArePossible.push_back(PossibleMovement::RightDown);
			//		whatMovementsArePossible.push_back(PossibleMovement::LeftDown);
			//		whatMovementsArePossible.push_back(PossibleMovement::LeftUp);
			//	}
			//}
			//else if(m_QBertFieldData.Row == 6)
			//{
			//	//can only go up
			//	whatMovementsArePossible.push_back(PossibleMovement::LeftUp);
			//	whatMovementsArePossible.push_back(PossibleMovement::RightUp);
			//}
			//else
			//{
			//	//can do anything
			//	whatMovementsArePossible.push_back(PossibleMovement::LeftUp);
			//	whatMovementsArePossible.push_back(PossibleMovement::RightUp);
			//	whatMovementsArePossible.push_back(PossibleMovement::RightDown);
			//	whatMovementsArePossible.push_back(PossibleMovement::LeftDown);
			//}
			 
			//if one => do that movement 
			//if (whatMovementsArePossible.size() == 1)
			//if ()
			//{
			//	////do that movement
			//	//switch (whatMovementsArePossible[0])
			//	//{
			//	//case PossibleMovement::LeftDown:
			//	//	m_pCommandMoveLeftDown->Execute();
			//	//	break;
			//	//case PossibleMovement::LeftUp:
			//	//	m_pCommandMoveLeftUp->Execute();
			//	//	break;
			//	//case PossibleMovement::RightDown:
			//	//	m_pCommandMoveRightDown->Execute();
			//	//	break;
			//	//case PossibleMovement::RightUp:
			//	//	m_pCommandMoveRightUp->Execute();
			//	//	break;
			//	//default:
			//	//	break;
			//	//}
			//}
			if(true)
			{
				//else
				//get player location
				if (m_pQBerts.size() > 1)
				{
					//do shit
					std::cout << "more then 1 Qbert";
				}
				else
				{
					//do coily.row - player.row = rowResult
					//&& coily.col - player.col = colResult
					int rowResult =  m_QBertFieldData.Row -  m_pQBerts[0]->GetFieldDataPlayer().Row;
					int colResult = m_QBertFieldData.Column -  m_pQBerts[0]->GetFieldDataPlayer().Column;


					if (colResult <= 0 && rowResult <= 0)
					{

						//move rightBottom
						//for (size_t i = 0; i < whatMovementsArePossible.size(); ++i)
						//{
						//	if (whatMovementsArePossible[i] == PossibleMovement::RightDown)
						//	{
								m_pCommandMoveRightDown->Execute();
								return;
							//}
						//}
					}
					if (colResult >= 0 && rowResult <= 0)
					{

						//for (size_t i = 0; i < whatMovementsArePossible.size(); ++i)
						//{
						//	if (whatMovementsArePossible[i] == PossibleMovement::LeftDown)
						//	{
								m_pCommandMoveLeftDown->Execute();
								return;
						//	}
						//}
					}
					if (colResult <= 0 && rowResult >= 0)
					{
						/*					for (size_t i = 0; i < whatMovementsArePossible.size(); ++i)
											{
												if (whatMovementsArePossible[i] == PossibleMovement::RightUp)
												{*/
						m_pCommandMoveRightUp->Execute();
						return;
						//}
					//}
					}
					if (colResult >= 0 && rowResult >= 0)
					{

					//	for (size_t i = 0; i < whatMovementsArePossible.size(); ++i)
					//	{
					//		if (whatMovementsArePossible[i] == PossibleMovement::LeftUp)
					//		{
								m_pCommandMoveLeftUp->Execute();
								return;
				//			}
				//		}
					}
					std::cout << "no movement";
				}
	
				//then see the one with the greatest distance.
				//do the one with the greatest distance 
				//=> if colResult == negative move right else move left
				//=> if rowResult == negative move bottom else move top
			}

			
		}
	}

}