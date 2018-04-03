//!
//! \file Main.cxx
//! \brief Programme de tests.
//! \author Mathieu MARTINEZ, Sonita NOP, Gabriel TCHIERNACK, Agnés PHILLIPPS
//! \version 0.1
//! \date 12 Janvier 2015
//!
//! Projet semestre 1 premiére année, NumberCrush
//!

#include <iostream>
#include <string>
#include <vector>
#include <iomanip> 
#include <cctype>
#include <stdlib.h>
#include <utility>  //swap
#include <fstream>
#include <time.h>
#include <limits>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <fstream>

//! \namespace std
using namespace std;


typedef vector <unsigned> CVLine; /*!< One line of the grid */

typedef vector <CVLine> CMat; /*!< vector without contains the Grid */

typedef pair <unsigned, unsigned> CPosition; /*!< pair which contains Line(.first) / column(.second) */

typedef pair <string, string> CScore; /*!< pair which contains pseudo(.first) / Score,level(.second) */

typedef vector <CScore> CVScoreRegister; /*!< \brief Vector which contains the informtions to save in files */

/********************************************************************************************************************************
*
*							ClearScreen & Couleur & WelcomeCinFail & GridSizeFail & GameChoiceFail & CinFail
*
***********************************************************************************************************************************/

//!\fn void ClearScreen ()
//! \brief Clear the screen.

void ClearScreen () // Clear the screen
{
    cout << "\033[H\033[2J";
}// ClearScreen()

//!\fn void Couleur (const string & coul)
//! \brief Affiche en couleur.
//! \param[in] const string & coul)

void Couleur (const string & coul) // Allow the Display of color
{
	cout << "\033[" << coul << "m";
}// Couleur()

//!
//!\fn bool WelcomeCinFail (const char LetsGo)
//! \brief Cin test fonction.
//!
//! \param[in] const char LetsGo is the parameter that we test.
//! \return True if Cin failed or False if Cin didn't fail.

bool WelcomeCinFail (const char LetsGo)
{
	if (cin.fail() || (LetsGo !=  'q'  && LetsGo != 'Q' && LetsGo !=  'e'  && LetsGo != 'E' )) 
	{
		cout << "Essayez encore Q soit q pour jouer" << endl;
		cout << "Soit E ou e pour partir" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return true;
	}
	return false;
}// WelcomeCinFail()

//!
//!\fn bool GridSizeFail (const unsigned GridSize)
//! \brief CinFail test fonction.
//!
//! \param[in] const char GridSize is the parameter that we test.
//! \return True if Cin failed or False if Cin didn't fail.

bool GridSizeFail (const unsigned GridSize)
{
	if (cin.fail() || GridSize < 2)
	{
		cout << "Essayez encore mais un nombre > 0" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return true;
	}
	return false;
} // GridSizeFail()

//!
//!\fn bool GameChoiceFail (const unsigned GameChoice)
//! \brief CinFail test fonction.
//!
//! \param[in] const unsigned GameChoice is the parameter that we test.
//! \return True if Cin failed or False if Cin didn't fail.

bool GameChoiceFail (const unsigned GameChoice) // All replay question are controled here
{
	if (cin.fail() || (GameChoice !=  1  && GameChoice != 2))
	{
		cout << "Essayez encore 1 soit 2" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return true;
	}
	return false;
}//GameChoiceFail()


//!\fn bool GameChoiceFail2 (const unsigned GameChoice)
//! \brief CinFail test fonction for Game Mode 
//!
//! \param[in] const unsigned GameChoice is the parameter that we test.
//! \return True if Cin failed or False if Cin didn't fail.

bool GameChoiceFail2 (const unsigned GameChoice) // GameMode Choice
{
	if (cin.fail() || (GameChoice !=  1  && GameChoice != 2 && GameChoice != 3 && GameChoice != 4 && GameChoice != 5))
	{
		cout << "Essayez encore 1 soit 2" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return true;
	}
	return false;
}//GameChoiceFail()

//!\fn bool CinFail (const CMat Grid, const CPosition Pos)
//! \brief CinFail test fonction for Position 
//! \param[in] const CMat Grid for the size.
//!  \param[in] const CPosition Pos is the parameter than we test
//! \return True if Cin failed or False if Cin didn't fail.

bool CinFail (const CMat Grid, const CPosition Pos) // Candies mouvements informations
{
	if (cin.fail() || Pos.first > Grid.size() || Pos.second > Grid.size())
	{
		cout << "Essayez encore" << endl;
		cin.clear(); // on nettoie le flux
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return true;
	}
	return false;
} // CinFail()

//!\fn bool CinDirectionFail (const char Direction)
//! \brief CinFail test fonction for Position 
//! \param[in] const char Direction is the parameter that we test.
//! \return True if Cin failed or False if Cin didn't fail.

bool CinDirectionFail (const char Direction)
{
	if (cin.fail() || !isalpha(Direction))
	{
		cout << "Essayez encore" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return true;
	}
	return false;
}//CinDirectionFail()

//! \fn bool BombeCoordFail (const CMat Grid, const CPosition PosBombe)
//! \brief CinFail test fonction for Position 
//! \param[in] const CMat Grid for the size.
//!  \param[in] const CPosition PosBombe is the parameter than we test
//! \return True if Cin failed or False if Cin didn't fail.

bool BombeCoordFail (const CMat Grid, const CPosition PosBombe) // While the bombe coord isn't right
{
	if (cin.fail() || PosBombe.first + 1 > Grid.size() || PosBombe.second + 1 > Grid.size())
	{
		cout << "il faut que toute l'explosion soit dans la grille, faites donc en sorte de la placer correctement" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return true;
	}
	return false;
}//BombeCoordFail()

/*********************************************************************************************************************************
*
*																	DisplayGrid
*
**********************************************************************************************************************************/

//! \fn void DisplayGrid (const CMat Grid)
//! \brief Display the Grid
//! \param[in] const CMat Grid for the size.

void DisplayGrid (const CMat Grid)
{
	const string KReset   ("0");
	const string KNoir    ("30");
	const string KRouge   ("31");
	const string KVert    ("32");
	const string KJaune   ("33");
	const string KBleu    ("34");
	const string KMagenta ("35");
	const string KCyan    ("36");
	ClearScreen();
	Couleur (KReset);
	unsigned Space (3);
	cout << "0|" ;
	for (unsigned i(0); i < Grid.size(); i++)
	{
		cout << setw(Space) << i + 1;
	}
	cout << endl;
	for (unsigned i(0); i < Grid.size() + 2 ; i++)
	{
		cout << setw(Space) << "---";
	}
	cout << endl;
	for (unsigned i (0); i< Grid.size(); i++)
		{
			cout << i + 1 << '|';
			for (unsigned j (0); j < Grid[i].size(); j++)
		 		{
					Couleur (KReset);
					switch(Grid[i][j])
					{
						case 0:
							Couleur(KNoir);
							cout << setw(Space) << Grid[i][j];
							break;
						case 1:
							Couleur(KRouge);
							cout << setw(Space) << Grid[i][j];
							break;
						case 2:
							Couleur(KVert);
							cout << setw(Space) << Grid[i][j];
							break;
						case 3:
							Couleur(KJaune);
							cout << setw(Space) << Grid[i][j];
							break;
						case 4:
							Couleur(KBleu);
							cout << setw(Space) << Grid[i][j];
							break;
						case 5:
							Couleur(KMagenta);
							cout << setw(Space) << Grid[i][j];
							break;
						case 6:
							Couleur(KCyan);
							cout << setw(Space) << Grid[i][j];
							break;
						case 7:
							cout << setw(Space) << '@';
							break;
						default:
							cout << setw(Space) << ' ';
							break;
					}
				}
			Couleur (KReset);
			cout << setw(Space) << '|' << i + 1;
			cout << endl;
		}
		for (unsigned i(0); i < Grid.size() + 2 ; i++)
		{
			cout << setw(Space) << "---";
		}
		cout << endl;
		cout << "0|";
		for (unsigned i(0); i < Grid.size(); i++)
		{
			cout << setw(Space) <<  i + 1;
		}
		cout << endl << endl << endl;
}//DisplayGrid()
/*************************************************************************************************************************************************
*
*				Replace & NoOneInColumn & IsGameStillPlayable & DeleteLine & DeleteColumn
*
***************************************************************************************************************************************************/

//! \fn void ReplaceColumnRight (CMat &Grid, const CPosition Pos, const unsigned NbCandies, const unsigned HowMany, const unsigned TypeGrid)
//! \brief Replace HowMany numbers in one line and move up the bottom
//! \param[in, out] CMat &Grid the Grid which we play on
//! \param[in] const CPosition Pos The Lines and Columns
//! \param[in] const unsigned NbCandies for the news created numbers
//! \param[in] const unsigned HowMany tell us how many move we have to do
//! \param[in] const unsigned TypeGrid tell us wich Number use to replace (Depends on Grid type)

void ReplaceColumnRight (CMat &Grid, const CPosition Pos, const unsigned NbCandies, const unsigned HowMany, const unsigned TypeGrid)
{
	unsigned KVal (0);
	unsigned Max = Grid[Pos.first].size() - Pos.first - 1;
	for (unsigned SameCandies(0); SameCandies < HowMany ; ++SameCandies)
		for (unsigned k(0); k < Max ; ++k)
		{
			Grid[Pos.first + k][Pos.second + SameCandies]=Grid[Pos.first + k + 1][Pos.second + SameCandies]; //Cela nous permet de décaler une ligne vers le haut en parcourant de la gauche vers la droite
		}
		for (unsigned k(0); k < HowMany; ++k)
		{
			if (TypeGrid == 1) KVal = 90;
			else KVal = rand() % NbCandies + 0;
			Grid[Grid[Pos.first].size() - 1][Pos.second + k]=KVal;
		}
}//ReplaceColumnRight()

//! \fn void ReplaceLineBot (CMat &Grid, const CPosition Pos, const unsigned NbCandies, const unsigned HowMany, const unsigned TypeGrid)
//! \brief Replace HowMnay numbers in one Column and move up the bottom
//! \param[in, out] CMat &Grid the Grid which we play on
//! \param[in] const CPosition Pos The Lines and Columns
//! \param[in] const unsigned NbCandies for the news created numbers
//! \param[in] const unsigned HowMany tell us how many move we have to do
//! \param[in] const unsigned TypeGrid tell us wich Number use to replace (Depends on Grid type)

void ReplaceLineBot (CMat &Grid, const CPosition Pos, const unsigned NbCandies, const unsigned HowMany, const unsigned TypeGrid)
{
	unsigned KVal (0);
	unsigned Max = Grid[Pos.first].size() - Pos.first - 1 ;
	for (unsigned m (0); m < HowMany ; ++m)
		for (unsigned k(0); k < Max ; ++k)
		{
			Grid[Pos.first + k][Pos.second]=Grid[Pos.first + k + 1][Pos.second]; //Nous permet de décaler une colone vers le haut
		}
		for (unsigned k(0); k < HowMany ; ++k)
		{
			if (TypeGrid == 1) KVal = 90;
			else KVal = rand() % NbCandies + 0;
			Grid[Grid[Pos.first].size() -1 - k][Pos.second]=KVal;
		}
}//ReplaceLineBot()

//! \fn bool IsGameStillPlayable (const CMat Grid, const CPosition Pos, const unsigned NbCandies)
//! \brief Test if there is at least one triple in the game 
//! \param[in] const CMat Grid the Grid which we play on
//! \param[in] const CPosition Pos The Lines and Columns
//! \param[in] const unsigned NbCandies for the news created numbers (rand)

bool IsGameStillPlayable (const CMat Grid, const CPosition Pos, const unsigned NbCandies) // Un des facteurs pour que le jeu soit toujours jouable
{
	unsigned PossValCompt (0); // Valeur qui va augmenter en fonction des mêmes chiffres présents afin de les compter et vérifier si il y en a plus de 3
	for (unsigned t (0) ; t < NbCandies ; ++t) //for every candies of NbCandies we'll test if there are at least 3 same or not
	{
		PossValCompt = 0; //Same Candies Compt
		for (unsigned m (0); m < Grid.size() ; ++m) // We are going through the grid
		{
			for (unsigned k (0); k < Grid[m].size() ; ++k) // same
			{
				if (Grid[m][k] == t) //If we find one candies
				{
					++PossValCompt; // we up the compt
					if (PossValCompt == 3) return true; // if there is 3 same candies so the game is still playable
				}
			}
		}
	}
	return false;
} // IsGameStillPlayable()

//! \fn void NoOneInColumn(CMat &Grid)
//! \brief Test if there is at least one empty colum in the game, if yes it moves to the right the reste of the grid
//! \param[in, out] CMat &Grid the Grid which we play on

void NoOneInColumn(CMat &Grid)
{
	unsigned Compt (0);
	for (unsigned MoreThanOneEmpty (0); MoreThanOneEmpty < Grid.size() - 1 ; ++ MoreThanOneEmpty) // while we didnot go through all the Grid
	{
		for (unsigned z (0) ; z < Grid.size() ; ++z) // we go case by case
		{
			Compt = 0;
			for (unsigned y (0) ; y < Grid[z].size() - 1 ; ++y) // We detect empty one
			{
				if (Grid[y][z] == 90)
					++Compt;
				if (Compt == Grid[z].size() - 1) // If the compt == Grid.size - 1 it means that there is one empty column
				{
					for (unsigned x (0) ; x < Grid[z].size(); ++x)
						for (unsigned u (0); u + z < Grid[z].size() - 1; ++ u) // We move up the column to the left
							Grid[x][z + u ] = Grid[x][z + 1 + u];
					for ( unsigned l (0); l < Grid.size() ; ++l) // We put empty case at the end 
						Grid[l][Grid.size() -1] = 90;
				}
			}
		}
	}
}//NoOneInColumn()

//! \fn void DeleteLine(CMat &Grid, const CPosition Position, const unsigned TypeGrid, const unsigned NbCandies)
//! \brief Delete one line if 3 little bombes (@) are link 
//! \param[in, out] CMat &Grid the Grid which we play on
//! \param[in] const CPosition Pos The Lines and Columns
//! \param[in] const unsigned TypeGrid make us know what type of grid we are playing on
//! \param[in] const unsigned NbCandies for the news created numbers (rand)

void DeleteLine(CMat &Grid, const CPosition Position, const unsigned TypeGrid, const unsigned NbCandies)
{
	unsigned KVal (0);
	for (unsigned m(0); m < Grid.size() ; ++m)
		for (unsigned k(0); Position.first + k < Grid.size() - 1 ; ++k)
		{
			Grid[Position.first + k][m]=Grid[Position.first + k + 1][m]; //Move up a line
		}
	for (unsigned Column (0); Column < Grid.size(); ++Column)
	{
		if (TypeGrid == 1) KVal = 90;
		else KVal = rand() % NbCandies + 0;
		Grid[Grid.size() - 1][Column]=KVal;
	}
}//NoOneInColumn()

//! \fn DeleteColumn(CMat &Grid, const CPosition Position, const unsigned TypeGrid, const unsigned NbCandies)
//! \brief Delete one line if 3 little bombes (@) are link 
//! \param[in, out] CMat &Grid the Grid which we play on
//! \param[in] const CPosition Pos The Lines and Columns
//! \param[in] const unsigned TypeGrid make us know what type of grid we are playing on
//! \param[in] const unsigned NbCandies for the news created numbers (rand)

void DeleteColumn(CMat &Grid, const CPosition Position, const unsigned TypeGrid, const unsigned NbCandies)
{
	unsigned KVal (0);
	for (unsigned m (0); m < Grid.size() ; ++m)
		for (unsigned k(0); k < Grid.size() - 1 ; ++k)
		{
			Grid[k][Position.second]=Grid[k + 1][Position.second]; //Move up a column
		}
	for (unsigned Line (0); Line < Grid.size(); ++Line)
	{
		if (TypeGrid == 1) KVal = 90;
		else KVal = rand() % NbCandies + 0;
		Grid[Line][Position.second]=KVal;
	}
}//DeleteColum()

/*******************************************************************************************************************
*
*							InitGrid && InformationsMouvement && MakeAMove 
*
***********************************************************************************************************************/

//! \fn void InitGrid (CMat &Grid, const unsigned GridSize, const unsigned NbCandies)
//! \brief Creats the Grid we are going to play with
//! \param[in, out] CMat &Grid the Grid which we play on
//! \param[in] const GridSize is the size of the Grid
//! \param[in] const unsigned NbCandies for the news created numbers (rand)

void InitGrid (CMat &Grid, const unsigned GridSize, const unsigned NbCandies)
{
	for (unsigned i(0); i < GridSize; ++i)
		for (unsigned j(0); j < GridSize; ++j)
			{
				int NbHasard = rand() % NbCandies + 0;
				Grid[i].push_back (NbHasard);
			}
}//InitGrid()

//! \fn void InformationsMouvement (const CMat Grid, CPosition &Pos, char &Direction)
//! \brief Ask the informations we need to play (Line, column, direction)
//! \param[in] const CMat Grid the Grid which we play on
//! \param[in, out] CPosition &Pos is the position the player has selected (Line & Column)
//! \param[in, out] char &Direction is the direction where he wants to swap (top, left right, back)


void InformationsMouvement (const CMat Grid, CPosition &Pos, char &Direction) //Informations about the move
{
	cout << "Saississez votre ligne: (seulement un entier > 0)" << endl;
	cin >> Pos.first;// We read what is taping the player
	while (CinFail(Grid, Pos)) cin >> Pos.first; // If cinfail so we call CinFail()
	if (Pos.first != 0) --Pos.first; // We do less 1 to the position to have the great one in the grid
	cout <<"Saississez les nombres à permuter(colone):" << endl; // we do the same here
	cin >> Pos.second;
	while (CinFail(Grid, Pos)) cin >> Pos.second;
	if (Pos.second != 0) --Pos.second;
	cout << "Saississez votre Direction ( z,s,q,d )" << endl;
	cin >> Direction;
	while (CinDirectionFail(Direction)) cin >> Direction;
}//InformationsMouvement()

//! \fn void MakeAMove (CMat &Grid, const CPosition Pos, char Direction)
//! \brief Making the move or telling it's not possible
//! \param[in, out] CMat &Grid the Grid which we play on
//! \param[in] const CPosition Pos is the position of the candy the play wants to swap
//! \param[in] const char Direction is the direction (rand)

void MakeAMove (CMat &Grid, const CPosition Pos, const char Direction)
{
	if ('z'== Direction && Pos.first >= 1 && Grid[Pos.first - 1][Pos.second] < 90 && Grid[Pos.first][Pos.second] < 90) //Move up
	{
		swap(Grid[Pos.first][Pos.second], Grid[Pos.first - 1][Pos.second]);//faire un switch
	}
	else if ('s' == Direction && Pos.first < (Grid.size() - 1) && Grid[Pos.first + 1][Pos.second] < 90 && Grid[Pos.first][Pos.second] < 90) // Move down
	{
		swap(Grid[Pos.first][Pos.second], Grid[Pos.first + 1][Pos.second]);
	} 
	else if ('d' == Direction && Pos.second < (Grid.size() - 1) && Grid[Pos.first][Pos.second + 1] < 90 && Grid[Pos.first][Pos.second] < 90) // Move right
	{
		swap(Grid[Pos.first][Pos.second], Grid[Pos.first][Pos.second + 1]);
	}
	else if ('q' == Direction && Pos.second >= 1 && Grid[Pos.first][Pos.second - 1] < 90 && Grid[Pos.first][Pos.second] < 90) // Move left
	{
		swap(Grid[Pos.first][Pos.second], Grid[Pos.first][Pos.second - 1]);
	}
	else  // If no value are correct so we ask the player to put a right movement
	{
		ClearScreen();
		cout << "Entrez une valeur utile s'il vous plaît, n'essayez pas de faire" << endl << "les malins en sortant de la grille !" << endl;
		this_thread::sleep_for (chrono::seconds(2));
	}

}//MakeAMove()

/******************************************************************************************************************************************************************************************************
*
*  GridWithoutTripleLine & GridWithoutTripleColumn & CleanfromTriple & BombeColum & BombeLine & GridWithTripleLittleBombeInColumn & GridWithTripleLittleBombeInLine && GridWithTripleLittleBombeInLine
*
******************************************************************************************************************************************************************************************************/

//! \fn bool GridWithoutTripleLine (CMat &Grid, CPosition &Pos, unsigned &HowMany, const unsigned NbCandies, const unsigned TypeGrid)
//! \brief Detect if there is at least 3 triple on a line and call the fonction ReplaceColumnRight
//! \param[in, out] CMat &Grid the Grid which we play on
//! \param[in, out] CPosition &Pos is the position of the candy
//! \param[in, out] unsigned &HowMany is the number of same candys link
//! \param[in, out] const unsigned NbCandies is the max diferent candies in the grid
//! \param[in] const unsigned TypeGrid tells us wich king of Grid it is 
//! \return true if there is at least 3 triple in a line, false other way

bool GridWithoutTripleLine (CMat &Grid, CPosition &Pos, unsigned &HowMany, const unsigned NbCandies, const unsigned TypeGrid)
{
	for (unsigned i (0); i< Grid.size(); i++)
		for (unsigned j (0); j<Grid[i].size()-2; j++)
		{
			if (Grid[i][j]==Grid[i][j + 1] && Grid[i][j] < 7) // if 2 candies are the same so we test the next one until they are different
			{
				HowMany = 0;
				while ( j + HowMany < Grid.size() && Grid[i][j] == Grid[i][j + HowMany] ) // while the candies are the same and we don't cross over the Grid, their number grows up (HowMany)
				{				
						HowMany += 1;
				}
				if (HowMany >= 3) // If they are 3 or more, we delete them
				{
					Pos.first = i; // Pos.first Take the value of the line where the first candy was finded
					Pos.second = j; // Pos.second Take the value of the column where the firt candy was finded
					ReplaceColumnRight(Grid, Pos, NbCandies, HowMany, TypeGrid);
					return true;
				}
			}
		}
	return false;
}//BeginGridWithoutTripleLine()

//! \fn bool GridWithoutTripleColumn (CMat & Grid, CPosition & Pos, unsigned & HowMany, const unsigned NbCandies, const unsigned TypeGrid)
//! \brief Detect if there is at least 3 triple on a column and call the fonction ReplaceLineBot
//! \param[in, out] CMat &Grid the Grid which we play on
//! \param[in, out] CPosition &Pos is the position of the candy
//! \param[in, out] unsigned &HowMany is the number of same candys link
//! \param[in, out] const unsigned NbCandies is the max of different candies in the grid
//! \param[in] const unsigned TypeGrid tells us wich king of Grid it is 
//! \return true if there is at least 3 triple in a column, false other way


bool GridWithoutTripleColumn (CMat &Grid, CPosition &Pos, unsigned &HowMany, const unsigned NbCandies, const unsigned TypeGrid) // On détect et remplace les triplets sur une colone
{
	for (unsigned i (0); i< Grid.size(); i++)
	{
		for (unsigned j (0); j<Grid[i].size()-2; j++)
		{
			if (Grid[j][i]==Grid[j + 1][i] && Grid[j][i] < 7) // si 2 valeur alignées d'une même colone sont identiques		
			{
				HowMany = 0;
				while (j + HowMany < Grid.size() && Grid[j][i]==Grid[j + HowMany][i])  // while the candies are the same and we don't cross over the Grid, their number grows up (HowMany)
				{
					HowMany += 1;
				}
				if (HowMany >= 3) // If they are 3 or more, we delete them
				{
					Pos.first= j; // Pos.first Take the value of the line where the first candy was finded
					Pos.second = i;// Pos.second Take the value of the column where the firt candy was finded
					ReplaceLineBot (Grid, Pos, NbCandies, HowMany, TypeGrid);			
					return true;
				}
			}
		}
	}
			
		return false;
}//BeginGridWithoutTripleColumn()

//! \fn void CleanGridFromTriple (CMat &Grid, CPosition &Position, unsigned &HowMany, const unsigned NbCandies, unsigned &Score, const unsigned TypeGrid)
//! \brief Detects if there is at least 3 triple of the same candy in the whole grid and delete them
//! \param[in, out] CMat &Grid the Grid which we play on
//! \param[in, out] CPosition &Position is the position of the candy
//! \param[in, out] unsigned &HowMany is the number of same candys link
//! \param[in, out] const unsigned NbCandies is the number max of different candies
//! \param[in, out] unsigned &Score grow up the score if needed
//! \param[in] const unsigned TypeGrid tells us wich king of Grid it is 

void CleanGridFromTriple (CMat &Grid, CPosition &Position, unsigned &HowMany, const unsigned NbCandies, unsigned &Score, const unsigned TypeGrid) 
{
	while (GridWithoutTripleLine (Grid, Position, HowMany, NbCandies, TypeGrid) || GridWithoutTripleColumn (Grid, Position, HowMany, NbCandies, TypeGrid))
	{
		if (HowMany == 3) 
		{
			Score = Score + 20;
			Grid[Position.first][Position.second]= 7 ;
		}
		else if (HowMany > 3) Score = Score + 20 * ( HowMany - 2);
	}
	HowMany = 0;
}// BeginCleanGridFromTriple()


/*******************************************************************************************************************************************
*
*															TheGameNormal & TheGameNormalSurvivorUse & TheGameSurvivor & BombeUlam & Ulam & Campagne & BombeColumn & BombeLine
*
***********************************************************************************************************************************************/

//! \fn void TriNombreOrdresDecroissant (CVScoreRegister &Recorder)
//! \brief Allows us to put the best score at the begining of the file
//! \param[in, out] CVScoreRegister &Recorder The vector of pair wich has the recorder of all the games

void TriNombreOrdresDecroissant (CVScoreRegister &Recorder) // Put numbers from the biggest to the lowest
{
    for (unsigned i (0); i < Recorder.size(); i++)
    {
        for (unsigned j(0); j < Recorder.size() - 1; j++)
        {
            if (Recorder[j].second < Recorder[j+1].second)
            {
                swap(Recorder[j], Recorder[j+1]);
            }
        }
    }
} //TriNombreOrdresDecroissant()

/*******************************************************************************************************************************************************************************************************
*
*											BombeLine/Column and All About BombeUlam 
*
********************************************************************************************************************************************************************************************************/

//! \fn void BombeColumn(CMat &Grid, CPosition &Position, unsigned &Score, const unsigned TypeGrid, const unsigned NbCandies)
//! \brief Grow up the score of the play and call the fonction DeleteColumn
//! \param[in, out] CMat &Grid is the grid where we play on
//! \param[in, out] CPosition &Position is the position of a candy (line and column)
//! \param[in, out] unsigned &Score is the current score of the player
//! \param[in] const unsigned TypeGrid tells us wich king of Grid it is
//! \param[in] const unsigned NbCandies is the number max of different candies


void BombeColumn(CMat &Grid, CPosition &Position, unsigned &Score, const unsigned TypeGrid, const unsigned NbCandies)
{
	for (unsigned Line (0); Line < Grid.size(); ++Line)
		if (Grid[Line][Position.second] < 7)
			Score = Score + Grid[Line][Position.second] * 2; // we add the score of the line
	DisplayGrid(Grid);
	DeleteColumn(Grid, Position, TypeGrid, NbCandies);
}// BombeColumn ()

//! \fn void BombeLine(CMat &Grid, CPosition &Position, unsigned &Score, const unsigned TypeGrid, const unsigned NbCandies)
//! \brief Grow up the score of the play and call the fonction DeleteLine
//! \param[in, out] CMat &Grid is the grid where we play on
//! \param[in, out] CPosition &Position is the position of a candy (line and column)
//! \param[in, out] unsigned &Score is the current score of the player
//! \param[in] const unsigned TypeGrid tells us wich king of Grid it is
//! \param[in] const unsigned NbCandies is the number max we can have in the grid

void BombeLine(CMat &Grid, CPosition &Position, unsigned &Score, const unsigned TypeGrid, const unsigned NbCandies)
{
	for (unsigned Column (0); Column < Grid.size(); ++Column)
		if (Grid[Position.first][Column] < 7)
			Score = Score + Grid[Position.first][Column] * 2;// we add the score of the line
	DisplayGrid(Grid);
	DeleteLine(Grid, Position, TypeGrid, NbCandies);
}//BombeLine

//! \fn bool GridWithTripleLittleBombeInColumn (CMat & Grid, CPosition &Position, unsigned & HowMany, const unsigned NbCandies, unsigned &Score, const unsigned TypeGrid)
//! \brief Detect if there is 3 triple little Bombe (@) on a column and call the fonction BombeColumn
//! \param[in, out] CMat &Grid the Grid which we play on
//! \param[in, out] CPosition &Position is the position of the candy
//! \param[in, out] unsigned &HowMany is the number of same candys link
//! \param[in] const unsigned NbCandies is the number max we can have in the grid
//! \param[in, out] unsigned &Score is the current score of the player
//! \param[in] const unsigned TypeGrid tells us wich king of Grid it is 
//! \return true if there is 3 triple little Bombe (@) in a column, false other way

bool GridWithTripleLittleBombeInColumn (CMat & Grid, CPosition &Position, unsigned & HowMany, const unsigned NbCandies, unsigned &Score, const unsigned TypeGrid)
{
	for (unsigned i (0); i< Grid.size(); i++)
	{
		for (unsigned j (0); j<Grid[i].size()-2; j++)
		{
			if (7==Grid[j][i] &&  7==Grid[j + 1][i]) // If we find 2 LittleBombes (@) are near
			{		
				HowMany=0;
				while (j + HowMany < Grid.size() && 7==Grid[j + HowMany][i])HowMany +=1 ;  // while LittleBombes (@) are near and we don't cross over the GridSize
			}
			if (3 <= HowMany) 
			{
				Position.second = i;
				BombeColumn(Grid, Position, Score, TypeGrid, NbCandies);
				HowMany = 0;
				return true;
			}
		}
	}
	return false;
}// GridWithTripleLittleBombeInLoumn()

//! \fn bool GridWithTripleLittleBombeInLine (CMat & Grid, CPosition &Position, unsigned & HowMany, const unsigned NbCandies, unsigned &Score, const unsigned TypeGrid)
//! \brief Detect if there is 3 triple Little Bombe (@) on a Line and call the fonction BombeLine
//! \param[in, out] CMat &Grid the Grid which we play on
//! \param[in, out] CPosition &Position is the position of the candy
//! \param[in, out] unsigned &HowMany is the number of same candys link
//! \param[in] const unsigned NbCandies is the number max we can have in the grid
//! \param[in, out] unsigned &Score is the current score of the player
//! \param[in] const unsigned TypeGrid tells us wich king of Grid it is 
//! \return true if there is at least 3 triple Little Bombe (@) in a column, false other way

bool GridWithTripleLittleBombeInLine (CMat & Grid, CPosition &Position, unsigned & HowMany, const unsigned NbCandies, unsigned &Score, const unsigned TypeGrid)
{
	for (unsigned i (0); i< Grid.size(); i++)
	{
		for (unsigned j (0); j<Grid[i].size()-2; j++)
		{
			if (Grid[i][j]==Grid[i][j + 1] && Grid[i][j] == 7) // If we find 2 LittleBombes (@) are near
			{
				HowMany = 0;
				while ( j + HowMany < Grid.size() && Grid[i][j] == Grid[i][j + HowMany] )HowMany += 1; // while LittleBombes (@) are near and we don't cross over the GridSize
			}
			if (3 <= HowMany) 
			{
				Position.first = i;
				BombeLine(Grid, Position, Score, TypeGrid, NbCandies);
				HowMany = 0;
				return true;
			}	
		}
	}
	return false;
}//GridWithTripleLittleBombeInLine()

//! \fn void CleanGridFromTripleBombes (CMat &Grid, CPosition &Position, unsigned &HowMany, const unsigned NbCandies, unsigned &Score, const unsigned TypeGrid) 
//! \brief Detect all the triple Little Bombe (@)
//! \param[in, out] CMat &Grid the Grid which we play on
//! \param[in, out] CPosition &Position is the position of the candy
//! \param[in, out] unsigned &HowMany is the number of same candys link
//! \param[in] const unsigned NbCandies is the number max we can have in the grid
//! \param[in, out] unsigned &Score is the current score of the player
//! \param[in] const unsigned TypeGrid tells us wich king of Grid it is 

void CleanGridFromTripleBombes (CMat &Grid, CPosition &Position, unsigned &HowMany, const unsigned NbCandies, unsigned &Score, const unsigned TypeGrid)  // While there are 3 (@) near
{
	while (GridWithTripleLittleBombeInLine (Grid, Position, HowMany, NbCandies, Score, TypeGrid) || GridWithTripleLittleBombeInColumn (Grid, Position, HowMany, NbCandies, Score, TypeGrid));
}//CLeanGridFromTripleBombes()

//! \fn void Ulam(CMat &Grid, CPosition &PosBombe, unsigned &Score, const unsigned TypeGrid, const unsigned NbCandies)
//! \brief Makes the Big Bombe exploses and replace the numbers destroyed
//! \param[in, out] CMat &Grid the Grid which we play on
//! \param[in, out] CPosition &PosBombe is the position of the candy
//! \param[in, out] unsigned &Score is the current score of the player
//! \param[in] const unsigned TypeGrid tells us wich king of Grid it is 
//! \param[in] const unsigned NbCandies is the number max we can have in the grid

void Ulam (CMat &Grid, CPosition &PosBombe, unsigned &Score, const unsigned TypeGrid, const unsigned NbCandies) // This is the explosion of the Bombe
{
	unsigned KVal (0);
	unsigned BombeSize (3);
	unsigned compt=2;
	unsigned x=2;
	CPosition PosBombeStock;
	PosBombeStock.first = PosBombe.first - BombeSize/2 -1;
	PosBombeStock.second = PosBombe.second - BombeSize/2 -1;
	Score += Grid[PosBombe.first - 1][PosBombe.second - 1];
	Grid[PosBombe.first - 1][PosBombe.second - 1]= KVal;
	while (compt < BombeSize * BombeSize) // This is the definition of the Ulam's circle
	{
		for ( unsigned i(0); i < x ; ++i)
		{	
			if (Grid[--PosBombe.first][PosBombe.second] < 7) 
			{
				Score = Score + Grid[PosBombe.first][PosBombe.second] * 2;
			}
			if (1 == TypeGrid) KVal = 90;
			else KVal = rand() % NbCandies + 0;
			Grid[PosBombe.first][PosBombe.second]= KVal;
			++compt;
		}
		for ( unsigned i(0); i < x ; ++i)
		{
			if (Grid[PosBombe.first][--PosBombe.second] < 7) 
			{
				Score = Score + Grid[PosBombe.first][PosBombe.second] * 2;
			}
			if (1 == TypeGrid) KVal = 90;
			else KVal = rand() % NbCandies + 0;
			Grid[PosBombe.first][PosBombe.second]= KVal;
			++compt;
		}
		for ( unsigned i(0); i < x ; ++i)
		{
			if (Grid[++PosBombe.first][PosBombe.second] < 7)
			{
				Score = Score + Grid[PosBombe.first][PosBombe.second] * 2;
			}
			if (1 == TypeGrid) KVal = 90;
			else KVal = rand() % NbCandies + 0;
			Grid[PosBombe.first][PosBombe.second]= KVal;
			++compt;
		}
		for ( unsigned i(0); i < x ; ++i)
		{
			if (Grid[PosBombe.first][++PosBombe.second] < 7 ) 
			{
				Score = Score + Grid[PosBombe.first][PosBombe.second] * 2;
			}
			if (1 == TypeGrid) KVal = 90;
			else KVal = rand() % NbCandies + 0;
			Grid[PosBombe.first][PosBombe.second]= KVal;
			++compt;
		}
	x=x+2;
	++PosBombe.first;
	++PosBombe.second;
	}
	unsigned Max = Grid[PosBombeStock.first].size() - PosBombeStock.first - 1; // We do the Max to don't cross (sermentation fault)
	for (unsigned a(0); a < BombeSize; ++a) // We mave while we don't cross over the bombe size
		for (unsigned m(0); m < BombeSize ; ++m) // we move the column while we didn't cross bombe size
			for (unsigned k(0); k < Max ; ++k) // while we are not at the bottom we move
			{
				Grid[PosBombeStock.first + k][PosBombeStock.second + m]=Grid[PosBombeStock.first + k + 1][PosBombeStock.second + m]; //We put a line to the top
			}
			for (unsigned b(0); b < BombeSize; ++b) // This is the place where the explosion is moved, where it's empty after explosion so we put KVal
				for (unsigned k(0); k < BombeSize; ++k)
				{
					if (1 == TypeGrid) KVal = 90;
					else KVal = rand() % NbCandies + 0;
					Grid[Grid[PosBombeStock.first].size() - 1 -b][PosBombeStock.second + k]=KVal;
				}
}// Ulam()

//! \fn void BombeUlam(CMat &Grid, unsigned &Score, const unsigned TypeGrid, const unsigned NbCandies)
//! \brief Asks where the players wants to make his Big Bombe to explose
//! \param[in, out] CMat &Grid the Grid which we play on
//! \param[in, out] unsigned &Score is the current score of the player
//! \param[in] const unsigned TypeGrid tells us wich king of Grid it is 
//! \param[in] const unsigned NbCandies is the number max we can have in the grid

void BombeUlam(CMat &Grid, unsigned &Score, const unsigned TypeGrid, const unsigned NbCandies) // We ask where the player want to explose the bombe
{
	cout << "Points: " << Score << endl;
	cout << "Vous avez débloqué une bombe, précisez l'endroit où vous voulez qu'elle explose (ligne) :" << endl;
	CPosition PosBombe;
	cin >> PosBombe.first;// On lit ce que rentre l'utilisateur
	while (BombeCoordFail (Grid, PosBombe) || PosBombe.first < 2) cin >> PosBombe.first; // Go ahead and enter right number
	cout <<"Saississez les nombres à permuter(colone):" << endl;
	cin >> PosBombe.second;
	while (BombeCoordFail (Grid, PosBombe) || PosBombe.second < 2) cin >> PosBombe.second;// Same

	Ulam(Grid, PosBombe, Score, TypeGrid, NbCandies);
} // BombeUlam()

//! \fn void BombeDetails (CMat &Grid, CPosition &Position, unsigned &Score, unsigned &HowMany, const unsigned NbCandies, unsigned &UseBombe, const unsigned TypeGrid)
//! \brief Calls the fonction BombeUlam, test if there is an empty Column, Display the Grid and says that one bombe have been used
//! \param[in, out] CMat &Grid the Grid which we play on
//! \param[in, out] CPosition &Position is the position of a candy (Line & Column)
//! \param[in, out] unsigned &Score is the current score of the player
//! \param[in, out] unsigned &HowMany is the number of same candys link
//! \param[in, out] unsigned &UseBombe is the number of Big bombe used
//! \param[in] const unsigned TypeGrid tells us wich king of Grid it is 
//! \param[in] const unsigned NbCandies is the number max we can have in the grid

void BombeDetails (CMat &Grid, CPosition &Position, unsigned &Score, unsigned &HowMany, const unsigned NbCandies, unsigned &UseBombe, const unsigned TypeGrid)
{
	BombeUlam (Grid, Score, TypeGrid, NbCandies);
	NoOneInColumn(Grid); // Is their an empty column?
	CleanGridFromTriple (Grid, Position, HowMany, NbCandies, Score, TypeGrid);
	DisplayGrid(Grid);
	UseBombe += 1;
}//BombeDetails()

//! \fn ScoreToHaveBombe (CMat &Grid, CPosition &Position, unsigned &HowMany, const unsigned NbCandies, unsigned &Score, const unsigned MaxScoreWin, unsigned &UseBombe, const unsigned GridSize, const unsigned TypeGrid)
//! \brief Tests if the player has the score to obtain a Big bombe
//! \param[in, out] CMat &Grid the Grid which we play on
//! \param[in, out] CPosition &Position is the position of a candy (Line & Column)
//! \param[in, out] unsigned &HowMany is the number of same candys link
//! \param[in] const unsigned NbCandies is the number max we can have in the grid
//! \param[in, out] unsigned &Score is the current score of the player
//! \param[in] const unsigned MaxScoreWin is the goal of the player
//! \param[in, out] unsigned &UseBombe is the number of Big bombe used
//! \param[in] const unsigned GridSize is the size of the Grid
//! \param[in] const unsigned TypeGrid tells us wich king of Grid it is 
//! \return true if the player has the score to obtain a Big Bombe, false other way

bool ScoreToHaveBombe (CMat &Grid, CPosition &Position, unsigned &HowMany, const unsigned NbCandies, unsigned &Score, const unsigned MaxScoreWin, unsigned &UseBombe, const unsigned GridSize, const unsigned TypeGrid)
{
	if (UseBombe == 0 && Score >= MaxScoreWin / 3)
	{
		BombeDetails (Grid, Position, Score, HowMany, NbCandies, UseBombe, TypeGrid);
		return true;
	}
	else if (UseBombe == 1 && Score >= MaxScoreWin / 2 ) 
	{
		BombeDetails (Grid, Position, Score, HowMany, NbCandies, UseBombe, TypeGrid);
		return true;
	}
	else if (UseBombe == 2 && Score >= (MaxScoreWin * 2) / 3)
	{
		BombeDetails (Grid, Position, Score, HowMany, NbCandies, UseBombe, TypeGrid);
		return true;
	}
	else return false;
}//ScoreToHaveBombe()

/*******************************************************************************************************************************************************************************************************
*
*			All About Register Mode 
*
*******************************************************************************************************************************************************************************************************/

//! \fn void TexteFileCampagneCreate (const string Recorder)
//! \brief Creat the file where the informations are going to be write
//! \param[in] const string Recorder is the file where the informations are goint to be saved

void TexteFileCampagneCreate (const string Recorder)
{
	ofstream CampagneLevel (Recorder, ofstream::out);
	CampagneLevel.close();
}//TexteFileCampagneCreate()

//! \fn void ScoreCampagneAffich (CVScoreRegister VScoreRegister)
//! \brief Display all the last Games
//! \param[in] const CVScoreRegister VScoreRegister is the vector where the informations of the last plays are recorded

void ScoreCampagneAffich (const CVScoreRegister VScoreRegister)
{
	unsigned lines = 0;
	while ( lines < VScoreRegister.size() - 1)  
    {  
		cout<< "Pseudo: "<< VScoreRegister[lines].first << " à marqué: " << VScoreRegister[lines].second << " Points" << endl;
		++lines;
	}  
}//ScoreCampagneAffich()

//! \fn void RegisterVectorCreate (CVScoreRegister &VRegister, CScore &PRegister, ifstream &ReadFile)
//! \brief Creats the vector where is going to be the information about last games
//! \param[in, out] CVScoreRegister &VRegister extracts the informations from ReadFile
//! \param[in, out] CScore &PRegister is the pair where pseudo(.first) and Score(.second) are recorded from ReadFile
//! \param[in, out] ifstream &ReadFile is the file where the informations of the last games are saved

void RegisterVectorCreate (CVScoreRegister &VRegister, CScore &PRegister, ifstream &ReadFile)
{
	string Line;
    while(!ReadFile.eof())
	{
		for ( unsigned Informations (0); Informations < 2 ; ++Informations) //in the file, it's line 1 : pseudo, line 2 : score line 3: pseudo, line 4 score, ... so :
		{
			if (Informations == 0) 
			{
				getline(ReadFile, Line); // all Pseudo are in .first
				PRegister.first = Line;
			}
			else 
			{
				getline(ReadFile, Line); // all score/level are in .Second
				PRegister.second = Line;
			}
		}
		VRegister.push_back(PRegister); // we raise the vector with the pair we just made
	} 
    ReadFile.close();
}//RegisterVectorCreate()

//! \fn void VectorMaker(CVScoreRegister &VScoreRegister, CScore &PScore, string Recorder)
//! \brief If the file Recorder exists, we make the vector, else we create the file Recorder
//! \param[in, out] CVScoreRegister &VRegister extracts the informations from ReadFile
//! \param[in, out] CScore &PScore is the pair where pseudo(.first) and Score(.second) are recorded from ReadFile
//! \param[in] const string Recorder is the file were the information is saved

void VectorMaker(CVScoreRegister &VScoreRegister, CScore &PScore, const string Recorder)
{
	ifstream ReadCampagneRegister (Recorder, ios::in);
	if(!ReadCampagneRegister.fail())
    {
    	RegisterVectorCreate (VScoreRegister, PScore, ReadCampagneRegister);        
    }
	else
       TexteFileCampagneCreate (Recorder); // If the file doesn't exist we creat it
}//VectorMaker()

//! \fn bool IsPseudoInFile (CVScoreRegister &VRegister, const string Pseudo, const unsigned Second)
//! \brief Tests if the player has already register his pseudo or not and register his name only if his new score > last score
//! \param[in, out] CVScoreRegister &VRegister extracts the informations from ReadFile
//! \param[in] const string Pseudo is the Pseudo of the player
//! \param[in, out] const unsigned Second is or the Score, or the Level that we have to register
//! return true if he found the pseudo, false other way

bool IsPseudoInFile (CVScoreRegister &VRegister, const string Pseudo, const unsigned Second)
{
	int Second2 = Second;
	for (unsigned Informations (0); Informations < VRegister.size(); ++Informations)
	{
		if (VRegister[Informations].first == Pseudo && stoi(VRegister[Informations].second) <= Second2) 
		{
			VRegister[Informations].second = to_string(Second);
			return true;
		}
	}	
	return false;
}//IsPseudoInFile()

//! \fn void PutInTheFile (CVScoreRegister &VRegister, CScore &PScore,const  string Pseudo, const unsigned Second, const string Recorder)
//! \brief if IsPseudoInFile, we replace all the file with news informations, else we put the informations at the end of the file
//! \param[in, out] CVScoreRegister &VRegister extracts the informations from ReadFile
//! \param[in, out] CScore &PScore is the pair where pseudo(.first) and Score(.second) are recorded from ReadFile
//! \param[in] const string Pseudo is the Pseudo of the player
//! \param[in, out] const unsigned Second is or the Score, or the Level that we have to register in the file
//! \param[in] const string Recorder is the file where we are going to put the informations about the last game

void PutInTheFile (CVScoreRegister &VRegister, CScore &PScore, const string Pseudo, const unsigned Second, const string Recorder)
{
	if (IsPseudoInFile (VRegister, Pseudo, Second))
	{
		ofstream CampagneLevel (Recorder, ofstream::out);
		for (unsigned NewFileLevel (0); NewFileLevel < VRegister.size() - 1; ++ NewFileLevel)
			for (unsigned PseudoLevel (0); PseudoLevel < 2 ; ++PseudoLevel)
			{
				if (PseudoLevel == 0) CampagneLevel << VRegister[NewFileLevel].first << endl;
				else CampagneLevel << VRegister[NewFileLevel].second << endl;
			}
		CampagneLevel.close();
	}
	else
	{
		ofstream CampagneLevel (Recorder, ofstream::app);
		CampagneLevel << Pseudo << endl;
		CampagneLevel << Second << endl;
		CampagneLevel.close();
	}
}//PutInTheFile()

//! \fn void CampagneLevelRegister (const unsigned Level, const unsigned TypeGrid)
//! \brief Creat the vector, extract informations from the file, save new informations
//! \param[in] const unsigned Level is the level we have to save in the file 
//! \param[in] const unsigned TypeGrid tells us wich type of Grid is used and also in wich files save the informations

void CampagneLevelRegister (const unsigned Level, const unsigned TypeGrid)
{
	CVScoreRegister VLevelRegister (0);
	CScore PLevel;
	string Pseudo;
	cout << "Saississez votre pseudo: " << endl;
	cin >> Pseudo;
	string LevelRecorder;
	if (TypeGrid == 1) LevelRecorder = "TexteFileCampagneLevelCreate.txt";
	else LevelRecorder = "TexteFileCampagneLevelType2Create.txt";
	VectorMaker(VLevelRegister, PLevel, LevelRecorder); 
	TriNombreOrdresDecroissant (VLevelRegister);
	PutInTheFile (VLevelRegister, PLevel, Pseudo, Level, LevelRecorder);
}//CampagneLevelRegister()

//! \fn void SurvivorCampagneRegister (const unsigned Score, const unsigned TypeGrid)
//! \brief Creats the vector, extract informations from the file, save new informations
//! \param[in] const unsigned Score is the score we have to save in the file 
//! \param[in] const unsigned TypeGrid tells us wich type of Grid is used and also in wich files save the informations

void SurvivorCampagneRegister (const unsigned Score, const unsigned TypeGrid)
{
	CVScoreRegister VScoreRegister (0);
	CScore PScore;
	string Pseudo;
	cout << "Saississez votre pseudo:" << endl;
	cin >> Pseudo;
	string ScoreRecorder;
	if (TypeGrid == 1) ScoreRecorder = "TexteFileCampagneRegisterCreate.txt";
	else ScoreRecorder = "TexteFileCampagneRegisterType2Create.txt";
	VectorMaker(VScoreRegister, PScore, ScoreRecorder);
	TriNombreOrdresDecroissant (VScoreRegister);
	PutInTheFile (VScoreRegister, PScore, Pseudo, Score, ScoreRecorder);
	VScoreRegister.clear();
	VectorMaker(VScoreRegister, PScore, ScoreRecorder);
	TriNombreOrdresDecroissant (VScoreRegister);
	cout << "voulez-vous afficher le palmarés des meilleurs score? 1: Oui, 2:Non" << endl;
	unsigned SeeScore (0);
	cin >> SeeScore;
	while (GameChoiceFail (SeeScore)) cin >> SeeScore;
	if (SeeScore == 1) ScoreCampagneAffich (VScoreRegister);
}//SurvivorCampagneRegister()

//! \fn bool FindPseudoInData (CVScoreRegister VScoreRegister, CScore PScore, string Pseudo, unsigned &Level)
//! \brief Allows the player to play where he stopped last time! We check his pseudo in he file, and if he has a pseudo he will play since his last level
//! \parem[in] const CVScoreRegister VScoreRegister is the vector where the informations from the file are extract
//! \param[in] const CScore PScore is the informations pseudo(.first) / Level(.second) we have to save in the file 
//! \param[in] const string Pseudo is the pseudo of the player
//! \param[in], out] unsigned &Level takes the value of the last level he stopped last time

bool FindPseudoInData (const CVScoreRegister VScoreRegister, const CScore PScore, const string Pseudo, unsigned &Level)
{
	for (unsigned PseudoRecorded (0); PseudoRecorded < VScoreRegister.size() - 1; ++PseudoRecorded)
			if (VScoreRegister[PseudoRecorded].first == Pseudo) 
			{
				Level = stoi(VScoreRegister[PseudoRecorded].second);
				return true;
			}
	return false;
}//FindPseudoInData()

//! \fn void FindWherePlayerStopped (unsigned &Level)
//! \brief If file LevelRecorder exists, it means that the player already played so maybe he has a pseudo recorded in so we ask him. 
//! \param[in, out] unsigned &Level takes the value of the last level he stopped last time

void FindWherePlayerStopped (unsigned &Level)
{
	unsigned HavePseudoOrNot (0);
	string Pseudo;
	string LevelRecorder = "TexteFileCampagneLevelCreate.txt";
	ifstream CampagneLevel (LevelRecorder, ofstream::in);
	if (CampagneLevel)
	{
		cout << "Si vous avez enregistré un pseudo, tapez 1, sinon tapez 2" << endl;
		cin >> HavePseudoOrNot;
		while (GameChoiceFail(HavePseudoOrNot)) cin >> HavePseudoOrNot;
		if (HavePseudoOrNot == 1)
		{
			cout << "Tapez votre pseudo:" << endl;
			cin >> Pseudo;
			CVScoreRegister VScoreRegister (0);
			CScore PScore;
			VectorMaker(VScoreRegister, PScore, LevelRecorder);
			if (!FindPseudoInData (VScoreRegister, PScore, Pseudo, Level)) cout << "Désolé, mais votre Pseudo n'a pas été trouvé, bon jeu!" << endl;
			else cout << " Bienvenu, " << Pseudo << " Vous rejouerez de la où vous vous êtes arrêté Niveau: " << Level << endl;
			CampagneLevel.close();
			this_thread::sleep_for (chrono::seconds(4)); 
		}
	}
}//FindWherePlayerStopped()

/*******************************************************************************************************************************************************************************************************
*
*			InformationsAndMakeMove && AskReplay && AskReplayCampagne
*
*******************************************************************************************************************************************************************************************************/

//! \fn void InformationsAndMakeMove (CMat &Grid, CPosition &Position, char &Direction, unsigned &HowMany, const unsigned NbCandies, unsigned &Score, const unsigned TypeGrid)
//! \brief takes all the informations about a swap, do it and clean the grid
//! \parem[in, out] CMat &Grid is the grid where we are playing
//! \param[in, out] CPosition &Position is the position of a candy line(.first) / column(.second)
//! \param[in, out] char &Direction is the direction where the player wants to swap (top, left, bot, right)
//! \param[in, out] unsigned &HowMany is the number of candy which are link
//! \param[in] const unsigned NbCandies is the max of different candies in the Grid
//! \param[in], out] unsigned &Score is the current score of the player
//! \param[in] const unsigned TypeGrid is the type of the grid we are playing on 

void InformationsAndMakeMove (CMat &Grid, CPosition &Position, char &Direction, unsigned &HowMany, const unsigned NbCandies, unsigned &Score, const unsigned TypeGrid)
{
	InformationsMouvement(Grid, Position, Direction);
	MakeAMove(Grid, Position, Direction);
	CleanGridFromTriple (Grid, Position, HowMany, NbCandies, Score, TypeGrid);
	CleanGridFromTripleBombes (Grid, Position, HowMany, NbCandies, Score, TypeGrid);
	NoOneInColumn(Grid); // On vérifie qu'il n'y a pas de colone vide
	CleanGridFromTriple (Grid, Position, HowMany, NbCandies, Score, TypeGrid);
	CleanGridFromTripleBombes (Grid, Position, HowMany, NbCandies, Score, TypeGrid);
	DisplayGrid(Grid);
}//InformationsAndMakeMove()

//! \fn void AskReplay (unsigned &RePlay)
//! \brief asks if the player wants to replay in normal mode
//! \param[in, out] unsigned &RePlay

void AskReplay (unsigned &RePlay)
{
	cout << "Voulez-vous rejouez? Si oui tapez 1 (Même taille de grille) sinon 2 (Pour changer de mode de jeu ou de grille)"  << endl;
	cin >> RePlay; // On demande à l'utilisateur s'il veut rejouer ou pas 
	while (GameChoiceFail(RePlay)) cin >> RePlay;
}//AskReplay()

//! \fn void AskReplayCampagne (unsigned &RePlay)
//! \brief asks if the player wants to replay in campagne mode
//! \param[in, out] unsigned &RePlay

void AskReplayCampagne (unsigned &RePlay)
{
	cout << "Voulez-vous passez au niveau suivant? Si oui tapez 1,  sinon 2 (Pour changer de mode de jeu)"  << endl;
	cin >> RePlay; // On demande à l'utilisateur s'il veut rejouer ou pas 
	while (GameChoiceFail(RePlay)) cin >> RePlay;
}//AskReplayCampagne()

/*******************************************************************************************************************************************************************************************************
*
*										The Differents Game Modes
*
********************************************************************************************************************************************************************************************************/

//! \fn void PlayNormalGame (CMat &Grid, CPosition &Position, const unsigned NbCandies, unsigned &HowMany, unsigned &Score, const unsigned MaxScoreWin, const unsigned GridSize, char &Direction, const unsigned TypeGrid, unsigned &NbMove)
//! \brief Launchs the normal game mode
//! \param[in, out] CMat &Grid is the grid where we are playing
//! \param[in, out] CPosition &Position is the position of a candy line(.first) / column(.second)
//! \param[in] const unsigned NbCandies is the max of different candies in the Grid
//! \param[in, out] unsigned &HowMany is the number of candy which are link
//! \param[in, out] unsigned &Score is the current score of the player
//! \param[in] const unsigned MaxScoreWin is the goal of the player
//! \param[in] const unsigned GridSize is the Size of the Grid we are playing on
//! \param[in, out] char &Direction is the direction where the player wants to swap (top, left, bot, right)
//! \param[in] const unsigned TypeGrid is the type of the grid we are playing on
//! \param[in, out] unsigned &NbMove is the number of moves that can make the player before lose

void PlayNormalGame (CMat &Grid, CPosition &Position, const unsigned NbCandies, unsigned &HowMany, unsigned &Score, const unsigned MaxScoreWin, const unsigned GridSize, char &Direction, const unsigned TypeGrid, unsigned &NbMove)
{
	unsigned UseBombe (1);
	if (GridSize > 9) UseBombe = 0;
	while (IsGameStillPlayable (Grid, Position, NbCandies)) 
	{
		if (TypeGrid == 2)
			cout << "Vous avez: " << NbMove << " Coups." << endl;
		while (!(MaxScoreWin <= Score) && ScoreToHaveBombe (Grid, Position, HowMany, NbCandies, Score, MaxScoreWin, UseBombe, GridSize, TypeGrid));
		if ( MaxScoreWin <= Score) 
		{
			cout << " Vous avez gagné !!!! Avec: " << Score << "Points" << endl;
			break;
		}
		cout << "Vous avez : " << Score << " Points et il vous faut atteindre : " << MaxScoreWin << " Points." << endl;
		InformationsAndMakeMove (Grid, Position, Direction, HowMany, NbCandies, Score, TypeGrid);
		if (TypeGrid == 2)
			--NbMove;
	}
}//PlayNormalGame()

//! \fn void TheGameNormal (CPosition &Position, char &Direction, unsigned &HowMany, const unsigned NbCandies, unsigned &Score, const unsigned MaxScoreWin, const unsigned GridSize, const unsigned TypeGrid)
//! \brief Prepares the launcher PlayNormalGame()
//! \param[in, out] CPosition &Position is the position of a candy line(.first) / column(.second)
//! \param[in, out] char &Direction is the direction where the player wants to swap (top, left, bot, right)
//! \param[in, out] unsigned &HowMany is the number of candy which are link
//! \param[in] const unsigned NbCandies is the max of different candies in the Grid
//! \param[in, out] unsigned &Score is the current score of the player
//! \param[in] const unsigned MaxScoreWin is the goal of the player
//! \param[in] const unsigned GridSize is the Size of the Grid we are playing on
//! \param[in] const unsigned TypeGrid is the type of the grid we are playing on

void TheGameNormal (CPosition &Position, char &Direction, unsigned &HowMany, const unsigned NbCandies, unsigned &Score, const unsigned MaxScoreWin, const unsigned GridSize, const unsigned TypeGrid) // Mode de jeu 1°)
{
	unsigned RePlay (1);
	while (RePlay == 1)
	{
		Score = 0;
		unsigned NbMove ( 12 + 2 * GridSize);
		CMat Grid (GridSize);
		InitGrid(Grid, GridSize, NbCandies);
		CleanGridFromTriple (Grid, Position, HowMany, NbCandies, Score, TypeGrid);
		DisplayGrid(Grid);
		PlayNormalGame (Grid, Position, NbCandies, HowMany, Score, MaxScoreWin, GridSize, Direction, TypeGrid, NbMove);
		AskReplay (RePlay);
	}
}//TheGameNormal()

//! \fn void TheGameNormalSurvivorUse (CMat &Grid, CPosition &Position, char &Direction, unsigned &HowMany, const unsigned NbCandies, unsigned &Score, const unsigned MaxScoreWin, const unsigned GridSize, const unsigned TypeGrid)
//! \brief Launchs the GameNormalSurvivor game mode
//! \param[in, out] CMat &Grid is the grid where we are playing
//! \param[in, out] CPosition &Position is the position of a candy line(.first) / column(.second)
//! \param[in, out] char &Direction is the direction where the player wants to swap (top, left, bot, right)
//! \param[in, out] unsigned &HowMany is the number of candy which are link
//! \param[in] const unsigned NbCandies is the max of different candies in the Grid
//! \param[in, out] unsigned &Score is the current score of the player
//! \param[in] const unsigned MaxScoreWin is the goal of the player
//! \param[in] const unsigned GridSize is the Size of the Grid we are playing on
//! \param[in] const unsigned TypeGrid is the type of the grid we are playing on

void TheGameNormalSurvivorUse (CMat &Grid, CPosition &Position, char &Direction, unsigned &HowMany, const unsigned NbCandies, unsigned &Score, const unsigned MaxScoreWin, const unsigned GridSize, const unsigned TypeGrid)
{
	time_t ltimedebut, ltimefin; 
	time(&ltimedebut); 
	unsigned Sec (0); 
	unsigned UseBombe (1);
	if (GridSize > 9) UseBombe = 0;
	Score = 0;
	while (IsGameStillPlayable (Grid, Position, NbCandies))  
	{
		time (&ltimefin); 
		Sec = ltimefin - ltimedebut ;
		if ( Sec >= 45 ) 
		{
			break; 
			cout << "Désolé pour vous, le jeu est terminé, vous avez perdu mais vous pouvez retenté votre chance autant de fois que vous le voudrez!" << ltimefin - ltimedebut  << endl; 
		}
		CleanGridFromTriple (Grid, Position, HowMany, NbCandies, Score, TypeGrid); 
		time (&ltimefin);
		cout << "Points: " << Score << " sur: " << MaxScoreWin <<" et temps: " << 45 - Sec << endl;
		while (ScoreToHaveBombe (Grid, Position, HowMany, NbCandies, Score, MaxScoreWin, UseBombe, GridSize, TypeGrid));
		InformationsAndMakeMove (Grid, Position, Direction, HowMany, NbCandies, Score, TypeGrid);
		time (&ltimefin); 
		if (Score >= MaxScoreWin && Sec < 45)
		{
			cout << " Félicication, vous avez gagné en :" << Sec << "Secondes" << endl; 
			break; // On sort du jeu
		}
	}
} // TheGameNormalSurvivorUse()

//! \fn void TheGameSurvivor (CPosition &Position, char &Direction, unsigned HowMany, const unsigned NbCandies, unsigned &Score, const unsigned MaxScoreWin, const unsigned GridSize, const unsigned TypeGrid)
//! \brief Prepares the launcher TheGameNormalSurvivorUse()
//! \param[in, out] CPosition &Position is the position of a candy line(.first) / column(.second)
//! \param[in, out] char &Direction is the direction where the player wants to swap (top, left, bot, right)
//! \param[in, out] unsigned &HowMany is the number of candy which are link
//! \param[in] const unsigned NbCandies is the max of different candies in the Grid
//! \param[in, out] unsigned &Score is the current score of the player
//! \param[in] const unsigned MaxScoreWin is the goal of the player
//! \param[in] const unsigned GridSize is the Size of the Grid we are playing on
//! \param[in] const unsigned TypeGrid is the type of the grid we are playing on

void TheGameSurvivor (CPosition &Position, char &Direction, unsigned HowMany, const unsigned NbCandies, unsigned &Score, const unsigned MaxScoreWin, const unsigned GridSize, const unsigned TypeGrid) 
{
	unsigned Begin (1);  
	while (Begin == 1)
	{
		cout << "Dans ce mode de jeu, vous aurez 45 secondes pour marquer le plus grand score" << endl;
		cout << "tapez 1 pour commencer ou 2 pour quitter" << endl; 
		cin >> Begin;
		while (GameChoiceFail (Begin)) cin >> Begin ; 
		if (Begin == 2) break; 
		while (Begin == 1) 
		{
			CMat Grid (GridSize);
			InitGrid(Grid, GridSize, NbCandies);
			CleanGridFromTriple (Grid, Position, HowMany, NbCandies, Score, TypeGrid);
			DisplayGrid(Grid);
			cout << "Bien, maintenant si vous voulez vraiment vous lancer dans le jeu, taper 1, sinon 2. Le compte à rebour commencera directement aprés !" << endl; 
			cin >> Begin;
			while (GameChoiceFail (Begin)) cin >> Begin;
			if (Begin == 2) break; 
			TheGameNormalSurvivorUse (Grid, Position, Direction, HowMany, NbCandies, Score, MaxScoreWin, GridSize, TypeGrid); 
			AskReplay (Begin);
		}
	}
}//TheGameSurvivor()

//! \fn void PlayCampagneGame (CMat &Grid, CPosition &Position, char &Direction, unsigned &HowMany, const unsigned NbCandies, unsigned &Score, const unsigned MaxScoreWin, unsigned &GridSize, unsigned &Level, unsigned &NbMove, unsigned &RePlay, const unsigned TypeGrid)
//! \brief Launchs the CampagneGame game mode
//! \parem[in, out] CMat &Grid is the grid where we are playing
//! \param[in, out] CPosition &Position is the position of a candy line(.first) / column(.second)
//! \param[in, out] char &Direction is the direction where the player wants to swap (top, left, bot, right)
//! \param[in, out] unsigned &HowMany is the number of candy which are link
//! \param[in] const unsigned NbCandies is the max of different candies in the Grid
//! \param[in}, out] unsigned &Score is the current score of the player
//! \param[in] const unsigned MaxScoreWin is the goal of the player
//! \param[in] const unsigned GridSize is the Size of the Grid we are playing on
//! \param[in, out] unsigned &Level is the current Level of the player
//! \param[in, out] unsigned &NbMove is the number of move allowed at the player
//! \param[in, out] unsigned &RePlay is the choice of the player if he wants to play again or not
//! \param[in] const unsigned TypeGrid is the type of the grid we are playing on

void PlayCampagneGame (CMat &Grid, CPosition &Position, char &Direction, unsigned &HowMany, const unsigned NbCandies, unsigned &Score, const unsigned MaxScoreWin, unsigned &GridSize, unsigned &Level, unsigned &NbMove, unsigned &RePlay, const unsigned TypeGrid)
{
	unsigned UseBombe (1);
	if (GridSize > 9) UseBombe = 0;
	while (IsGameStillPlayable (Grid, Position, NbCandies))
	{
		cout << endl << "Niveau " << Level << endl << "Vous avez : " << NbMove << " Coups" << endl
			<< "Vous avez: " << Score << " Points" << " Et vous devez atteindre: " << MaxScoreWin << " Points" << endl << endl;
		while (ScoreToHaveBombe (Grid, Position, HowMany, NbCandies, Score, MaxScoreWin, UseBombe, GridSize, TypeGrid)) 
		{
			NbMove -= 1 ;
			cout << endl << "Niveau " << Level << endl << "Vous avez : " << NbMove << " Coups" << endl
				<< "Vous avez: " << Score << " Points" << " Et vous devez atteindre: " << MaxScoreWin << " Points" << endl << endl;
		}
		if ( Score >= MaxScoreWin )
		{
			Level = Level + 1;
			NbMove = 12 + GridSize * 3;
			cout << "Niveau fini! Pour aller au niveau suivant tapez 1, sinon 2. Sachez que votre progression sera enregistré si vous vous arrêtez." << endl;
			cin >> RePlay;
			while (GameChoiceFail(RePlay)) cin >> RePlay;
			break;
		}
		else if (NbMove == 0)
		{
			AskReplayCampagne (RePlay);
			if (RePlay == 2) CampagneLevelRegister (Level, TypeGrid);
			break;
		}
		InformationsAndMakeMove (Grid, Position, Direction, HowMany, NbCandies, Score, TypeGrid);
		NbMove = NbMove -1;
	}
}//PlayCampagneGame()

//! \fn void Campagne (CPosition &Position, char &Direction, unsigned &HowMany, const unsigned NbCandies, unsigned &Score, unsigned &MaxScoreWin, unsigned &GridSize, const unsigned TypeGrid)
//! \brief Prepares the launcher PlayCampagneGame()
//! \param[in, out] CPosition &Position is the position of a candy line(.first) / column(.second)
//! \param[in, out] char &Direction is the direction where the player wants to swap (top, left, bot, right)
//! \param[in, out] unsigned &HowMany is the number of candy which are link
//! \param[in] const unsigned NbCandies is the max of different candies in the Grid
//! \param[in, out] unsigned &Score is the current score of the player
//! \param[in, out] unsigned &MaxScoreWin is the goal of the player
//! \param[in, out] unsigned &GridSize is the Size of the Grid we are playing on
//! \param[in] const unsigned TypeGrid is the type of the grid we are playing on

void Campagne (CPosition &Position, char &Direction, unsigned &HowMany, const unsigned NbCandies, unsigned &Score, unsigned &MaxScoreWin, unsigned &GridSize, const unsigned TypeGrid)
{
	ClearScreen();
	unsigned RePlay (1);
	cout << "Bienvenue dans le mode campagne ! Dans ce mode, vous allez pouvoir jouer sur le jeu et chaque niveau passé deviendra de plus en plus long et compliqué. Vous avez un nombre de coups limités pour atteindre un certain score, à vous de jouer" << endl << " Pour continuer tapez 1, sinon 2 :" << endl;
	cin >> RePlay;
	while (GameChoiceFail(RePlay)) cin >> RePlay;
	unsigned Level (0);
	unsigned NbMove (14);
	FindWherePlayerStopped (Level);
	while (1 == RePlay)
	{
		GridSize = 5 + Level ;
		MaxScoreWin = GridSize * GridSize * 3;
		CMat Grid (GridSize);
		InitGrid(Grid, GridSize, NbCandies);
		CleanGridFromTriple (Grid, Position, HowMany, NbCandies, Score, TypeGrid);
		DisplayGrid(Grid);
		PlayCampagneGame (Grid, Position, Direction, HowMany, NbCandies, Score, MaxScoreWin, GridSize, Level, NbMove, RePlay, TypeGrid);
		Score = 0;
	}
}//Campagne()

//! \fn void PlaySurvivorCampagne(CMat &Grid, CPosition &Position, unsigned &HowMany, const unsigned NbCandies, unsigned &Score, char &Direction, const unsigned GridSize, unsigned MaxScoreWin, const unsigned TypeGrid, const unsigned Level)
//! \brief Launchs the SurvivorCampagne game mode
//! \parem[in, out] CMat &Grid is the grid where we are playing
//! \param[in, out] CPosition &Position is the position of a candy line(.first) / column(.second)
//! \param[in, out] unsigned &HowMany is the number of candy which are link
//! \param[in] const unsigned NbCandies is the max of different candies in the Grid
//! \param[in, out] unsigned &Score is the current score of the player
//! \param[in, out] char &Direction is the direction where the player wants to swap (top, left, bot, right)
//! \param[in] const unsigned GridSize is the Size of the Grid we are playing on
//! \param[in] const unsigned MaxScoreWin is the goal of the player
//! \param[in] const unsigned TypeGrid is the type of the grid we are playing on
//! \param[in] const unsigned Level is the current level of the player

void PlaySurvivorCampagne(CMat &Grid, CPosition &Position, unsigned &HowMany, const unsigned NbCandies, unsigned &Score, char &Direction, const unsigned GridSize, unsigned MaxScoreWin, const unsigned TypeGrid, const unsigned Level)
{
	time_t ltimedebut, ltimefin; 
	time(&ltimedebut); 
	unsigned Sec (0); 
	unsigned UseBombe (1);
	if (GridSize > 9) UseBombe = 0;
	while (IsGameStillPlayable (Grid, Position, NbCandies)) 
	{
		time (&ltimefin); 
		Sec = ltimefin - ltimedebut ;
		CleanGridFromTriple (Grid, Position, HowMany, NbCandies, Score, TypeGrid); 
		time (&ltimefin);
		if (Sec >= 45)
		{
			cout << " vous avez marqué : " << Score << " Points en: " << 45 * Level <<" Secondes" << endl;
			break; 
		}
		while (ScoreToHaveBombe (Grid, Position, HowMany, NbCandies, Score, MaxScoreWin, UseBombe, GridSize, TypeGrid))
		{	
			time (&ltimefin);
			cout << "Points: " << Score <<" et temps: " << 45 - Sec << endl;
		}
		time (&ltimefin);
		if ((45 - Sec) > 45) cout << cout << "Points: " << Score <<" et temps: " << 0 << endl;
		else cout << "Points: " << Score <<" et temps: " << 45 - Sec << endl;
		if (!IsGameStillPlayable (Grid, Position, NbCandies)) break;
		InformationsAndMakeMove (Grid, Position, Direction, HowMany, NbCandies, Score, TypeGrid);
	}
}//PlaySurvivorCampagne()

//! \fn void SurvivorCampagne(CPosition &Position, unsigned &HowMany, const unsigned NbCandies, unsigned &Score, unsigned &GridSize, char &Direction, unsigned &MaxScoreWin, const unsigned TypeGrid)
//! \brief Prepares the launcher PlaySurvivorCampagne()
//! \param[in, out] CPosition &Position is the position of a candy line(.first) / column(.second)
//! \param[in, out] unsigned &HowMany is the number of candy which are link
//! \param[in] const unsigned NbCandies is the max of different candies in the Grid
//! \param[in, out] unsigned &Score is the current score of the player
//! \param[in, out] unsigned &GridSize is the Size of the Grid we are playing on
//! \param[in, out] char &Direction is the direction where the player wants to swap (top, left, bot, right)
//! \param[in, out] unsigned MaxScoreWin is the goal of the player
//! \param[in] const unsigned TypeGrid is the type of the grid we are playing on

void SurvivorCampagne(CPosition &Position, unsigned &HowMany, const unsigned NbCandies, unsigned &Score, unsigned &GridSize, char &Direction, unsigned &MaxScoreWin, const unsigned TypeGrid)
{
	ClearScreen();
	unsigned RePlay (1);
	cout << "Bienvenue dans le mode SurvivorCampagne ! Dans ce mode, vous allez devoir marquer un maximum de score en 45 seconde pendant 10 niveaux. Dés que le temps se termine, vous passerez automatiquement au prochain niveau. Les scores seront enregistrés et classé en ordre décroissant, le but est de marquer le maximum de points durant ces 10 niveaux! Il est impossible de perdre, c'est un jeu de vitesse." << endl << "Pour continuer tapez 1, sinon 2 :" << endl;
	cin >> RePlay;
	while (GameChoiceFail(RePlay)) cin >> RePlay;
	unsigned Level (0);
	Score = 0;
	while (1 == RePlay && Level < 11)
	{
		GridSize = 5 + Level ;
		MaxScoreWin = GridSize * GridSize * 3 + Score;
		Level += 1;
		CMat Grid (GridSize);
		InitGrid(Grid, GridSize, NbCandies);
		CleanGridFromTriple (Grid, Position, HowMany, NbCandies, Score, TypeGrid);
		DisplayGrid(Grid);
		PlaySurvivorCampagne(Grid, Position, HowMany, NbCandies, Score, Direction, GridSize, MaxScoreWin, TypeGrid, Level);
		AskReplayCampagne(RePlay);
		if (RePlay == 2) SurvivorCampagneRegister (Score, TypeGrid);
			
	}
	if (Level == 11) cout << "Voila, vous avez fini, en espérant que cela vous à plu! " << endl;
}//SurvivorCampagne()

//! \fn void PlayLuckyLukeGame (CMat &Grid, CPosition &Position, unsigned &HowMany, const unsigned NbCandies, char &Direction, unsigned &Score, const unsigned TypeGrid)
//! \brief Launchs the LuckyLuke game mode
//! \param[in, out] CMat &Grid is the grid where we are playing
//! \param[in, out] CPosition &Position is the position of a candy line(.first) / column(.second)
//! \param[in, out] unsigned &HowMany is the number of candy which are link
//! \param[in] const unsigned NbCandies is the max of different candies in the Grid
//! \param[in, out] char &Direction is the direction where the player wants to swap (top, left, bot, right)
//! \param[in, out] unsigned &Score is the current score of the player
//! \param[in] const unsigned TypeGrid is the type of the grid we are playing on

void PlayLuckyLukeGame (CMat &Grid, CPosition &Position, unsigned &HowMany, const unsigned NbCandies, char &Direction, unsigned &Score, const unsigned TypeGrid)
{
	time_t ltimedebut, ltimefin; 
	time(&ltimedebut); 
	unsigned Sec (0); 
	time (&ltimefin);
	while (IsGameStillPlayable (Grid, Position, NbCandies))  
	{
		Sec= ltimefin - ltimedebut;
		CleanGridFromTriple (Grid, Position, HowMany, NbCandies, Score, TypeGrid);
		cout << "temps: " <<  Sec << endl;
		InformationsAndMakeMove (Grid, Position, Direction, HowMany, NbCandies, Score, TypeGrid);
		time (&ltimefin);
	}
}//PlayLuckyLuke()

//! \fn void LuckyLuke (CPosition &Position, char &Direction, unsigned &HowMany, const unsigned NbCandies, const unsigned GridSize, unsigned &Score, const unsigned TypeGrid)
//! \brief Prepares the LuckyLuke game mode
//! \param[in, out] CPosition &Position is the position of a candy line(.first) / column(.second)
//! \param[in, out] char &Direction is the direction where the player wants to swap (top, left, bot, right)
//! \param[in, out] unsigned &HowMany is the number of candy which are link
//! \param[in] const unsigned NbCandies is the max of different candies in the Grid
//! \param[in] const unsigned GridSize is the size of the grid
//! \param[in, out] unsigned &Score is the current score of the player
//! \param[in] const unsigned TypeGrid is the type of the grid we are playing on


void LuckyLuke (CPosition &Position, char &Direction, unsigned &HowMany, const unsigned NbCandies, const unsigned GridSize, unsigned &Score, const unsigned TypeGrid)
{
	ClearScreen();
	unsigned RePlay (1);
	cout << "Bienvenue dans le mode LuckyLuke ! Dans ce mode, vous allez devoir supprimer tous les triplets en un minimum de temps. Le but est de finir la grille avec le plus petit temps possible, le nombre de triplets restant ne vous sera pas afficher." << endl << "Pour continuer tapez 1, sinon 2 :" << endl;
	cin >> RePlay;
	while (GameChoiceFail(RePlay)) cin >> RePlay;
	while (1 == RePlay)
	{
		CMat Grid (GridSize);
		InitGrid(Grid, GridSize, NbCandies);
		CleanGridFromTriple (Grid, Position, HowMany, NbCandies, Score, TypeGrid);
		DisplayGrid(Grid);
		PlayLuckyLukeGame(Grid, Position, HowMany, NbCandies, Direction, Score, TypeGrid);
		AskReplay(RePlay);
	}
}//LuckyLuke()

//! \fn void MenuTrou (unsigned &GridSize , const unsigned NbCandies , unsigned &HowMany, char &Direction, unsigned &Score, unsigned MaxScoreWin, const unsigned TypeGrid)
//! \brief Prepares the LuckyLuke game mode
//! \param[in, out] unsigned &Gridsize
//! \param[in, out] char &Direction is the direction where the player wants to swap (top, left, bot, right)
//! \param[in, out] unsigned &HowMany is the number of candy which are link
//! \param[in, out] MaxScoreWin the goal for the player
//! \param[in] const unsigned NbCandies is the max of different candies in the Grid
//! \param[in, out] unsigned &Score is the current score of the player
//! \param[in] const unsigned TypeGrid is the type of the grid we are playing on

void MenuTrou (unsigned &GridSize , const unsigned NbCandies , unsigned &HowMany, char &Direction, unsigned &Score, unsigned MaxScoreWin, const unsigned TypeGrid)
{
	ClearScreen();
	cout << "Bienvenu sur le mode de jeu Plein! Ici, lorsque vous dégomerez au minimum un triplet " << endl
		<< "des nombres aléatoires apparaîtront, plutot que du vide" << endl
		<< " Les @ que vous verrez sont des petites bombes que vous débloqués si vous alignez seulement 3 chiffres" << endl
		<< " Si vous les alignez sur un ligne, toute la ligne explosera, si vous les aligné sur une colone, la colone explosera. " << endl
		<< "Atteint un certain score, vous débloquerez aussi une grosse bombe, il faudra choisir la ligne et la colone d'explosion." << endl << endl
		<< "Maintenant, nous vous proposons 5 modes de jeux, dont 2 campagnes: " << endl << endl
		<< "1°) Le jeu normal (atteindre un score)" << endl
		<< "2°) Le jeu Mode SpecialTooLate!" << endl
		<< "3°) Le jeu en mode campagne !" << endl
		<< "4°) Le jeu en mode campagne SpecialTooLate!" << endl
		<< "5°) Le jeu Luky Luck ! Vider la grille en un minimum de temps " << endl << endl
		<< "Tapez le chiffre du jeu auquel vous voulez jouer :" << endl;
		CPosition Position;
		unsigned GameChoice;
		cin >> GameChoice;
		while (GameChoiceFail2(GameChoice)) cin >> GameChoice;
		if (1 == GameChoice || 2 == GameChoice || 5 == GameChoice)
		{
			cout << "Saississez votre taille de grille:"<< endl;
			cin >> GridSize;
			while (GridSizeFail (GridSize)) cin >> GridSize;
			if (GameChoice == 1 )
			{	
				MaxScoreWin = GridSize * GridSize * 3;
				TheGameNormal (Position, Direction, HowMany, NbCandies, Score, MaxScoreWin, GridSize, TypeGrid);
			}
			else if (GameChoice == 2 )
			{
				MaxScoreWin = 3 * GridSize * GridSize ;
				TheGameSurvivor (Position, Direction, HowMany, NbCandies, Score, MaxScoreWin, GridSize, TypeGrid);
			}
			else if (GameChoice == 5 )
			{
				LuckyLuke (Position, Direction, HowMany, NbCandies, GridSize, Score, TypeGrid);
			}
		}
		else if (GameChoice == 3 )
		{
			Campagne (Position, Direction, HowMany, NbCandies, Score, MaxScoreWin, GridSize, TypeGrid);
		}
		else if (GameChoice == 4)
		{
			SurvivorCampagne(Position, HowMany, NbCandies, Score, GridSize, Direction, MaxScoreWin, TypeGrid);
		}
		Score = 0;
}

//! \fn void MenuTrouPlein (unsigned &GridSize , const unsigned NbCandies , unsigned &HowMany, char &Direction, unsigned &Score, unsigned MaxScoreWin, const unsigned TypeGrid)
//! \brief Prepares the LuckyLuke game mode
//! \param[in, out] unsigned &Gridsize
//! \param[in, out] char &Direction is the direction where the player wants to swap (top, left, bot, right)
//! \param[in, out] unsigned &HowMany is the number of candy which are link
//! \param[in, out] MaxScoreWin the goal for the player
//! \param[in] const unsigned NbCandies is the max of different candies in the Grid
//! \param[in, out] unsigned &Score is the current score of the player
//! \param[in] const unsigned TypeGrid is the type of the grid we are playing on

void MenuTrouPlein (unsigned &GridSize , const unsigned NbCandies , unsigned &HowMany, char &Direction, unsigned &Score, unsigned MaxScoreWin, const unsigned TypeGrid)
{
	ClearScreen();
	cout << "Bienvenu sur le mode de jeu Plein! Ici, lorsque vous dégomerez au minimum un triplet " << endl
		<< "des nombres aléatoires apparaîtront, plutot que du vide" << endl
		<< " Les @ que vous verrez sont des petites bombes que vous débloqués si vous alignez seulement 3 chiffres" << endl
		<< " Si vous les alignez sur un ligne, toute la ligne explosera, si vous les aligné sur une colone, la colone explosera. " << endl
		<< "Atteint un certain score, vous débloquerez aussi une grosse bombe, il faudra choisir la ligne et la colone d'explosion." << endl << endl
		<< "Maintenant, nous vous proposons 5 modes de jeux, dont 2 campagnes: " << endl << endl
		<< "1°) Le jeu normal (atteindre un score)" << endl
		<< "2°) Le jeu Mode SpecialTooLate!" << endl
		<< "3°) Le jeu en mode campagne !" << endl
		<< "4°) Le jeu en mode campagne SpecialTooLate!" << endl
		<< "5°) Le jeu Luky Luck ! Vider la grille en un minimum de temps " << endl << endl
		<< "Tapez le chiffre du jeu auquel vous voulez jouer :" << endl;
	CPosition Position;
	unsigned GameChoice;
	cin >> GameChoice;
	while (GameChoiceFail2(GameChoice)) cin >> GameChoice;
	if (1 == GameChoice || 2 == GameChoice || 5 == GameChoice)
		{
			cout << "Saississez votre taille de grille:"<< endl;
			cin >> GridSize;
			while (GridSizeFail (GridSize)) cin >> GridSize;
			if (GameChoice == 1 )
			{	
				MaxScoreWin = GridSize * GridSize * 6;
				TheGameNormal (Position, Direction, HowMany, NbCandies, Score, MaxScoreWin, GridSize, TypeGrid);
			}
			else if (GameChoice == 2 )
			{
				MaxScoreWin = 6 * GridSize * GridSize ;
				TheGameSurvivor (Position, Direction, HowMany, NbCandies, Score, MaxScoreWin, GridSize, TypeGrid);
			}
			else if (GameChoice == 5 )
			{
				LuckyLuke (Position, Direction, HowMany, NbCandies, GridSize, Score, TypeGrid);
			}
		}
	else if (GameChoice == 3 )
	{
		Campagne (Position, Direction, HowMany, NbCandies, Score, MaxScoreWin, GridSize, TypeGrid);
	}
	else if (GameChoice == 4)
	{
		SurvivorCampagne(Position, HowMany, NbCandies, Score, GridSize, Direction, MaxScoreWin, TypeGrid);
	}
	Score = 0;
}

//! \fn void Menu (unsigned &GridSize , const unsigned &NbCandies , unsigned &HowMany, char &Direction, unsigned &Score, unsigned MaxScoreWin, unsigned TypeGrid)
//! \brief Prepares the LuckyLuke game mode
//! \param[in, out] unsigned &Gridsize
//! \param[in, out] char &Direction is the direction where the player wants to swap (top, left, bot, right)
//! \param[in, out] unsigned &HowMany is the number of candy which are link
//! \param[in, out] MaxScoreWin the goal for the player
//! \param[in] const unsigned NbCandies is the max of different candies in the Grid
//! \param[in, out] unsigned &Score is the current score of the player
//! \param[in] const unsigned TypeGrid is the type of the grid we are playing on

void Menu (unsigned &GridSize , const unsigned &NbCandies , unsigned &HowMany, char &Direction, unsigned &Score, unsigned MaxScoreWin, unsigned TypeGrid)
{
	while (true)
	{
		cout << "Bienvenu sur le jeu NumberCrush ! Êtes-vous prés à passer un moment de pur bonheur? Si oui, tapez Q ou q, sinon  E ou e" << endl;
		char LetsGo;
		cin >> LetsGo;
		while (WelcomeCinFail (LetsGo)) cin >> LetsGo;
		if (LetsGo == 'e' || LetsGo =='E') break;
		cout << " Maintenant, vous avez le choix entre deux sortes de grilles, une grille à trou et l'autre pleine. Sur laquelle voulez-vous jouer ? 1:Trou/2:Pleine." << endl;
		cin >> TypeGrid;
		while (GameChoiceFail(TypeGrid)) cin >> TypeGrid;
		if (TypeGrid == 1)
		{
			MenuTrou (GridSize , NbCandies , HowMany, Direction, Score, MaxScoreWin, TypeGrid);
		}
		else
		{
			MenuTrouPlein (GridSize , NbCandies , HowMany, Direction, Score, MaxScoreWin, TypeGrid);
		}
	}
}
/*********************************************************************************************************************************************
*
*																Main()
*
**********************************************************************************************************************************************/

//! \fn int main() ()
//! \brief Main

int main()
{
	unsigned GridSize (0);
	const unsigned NbCandies (7);
	unsigned HowMany (0);
	char Direction;
	unsigned Score (0);
	unsigned MaxScoreWin (0);
	unsigned TypeGrid (0);
	srand (time(NULL));
	Menu (GridSize , NbCandies , HowMany, Direction, Score, MaxScoreWin, TypeGrid);
	cout << "Aurevoir et à bientôt !" << endl;
}// Main()
