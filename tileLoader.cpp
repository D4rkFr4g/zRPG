#include "tileLoader.h"


void tileLoader::loadTiles(const char* filename, TileLevel *level)
{
	/* PURPOSE:		Loads tile layout from flare.txt file
		RECEIVES:	filename - Filename corresponding to flare tile data
						level - object corresponding to the tile data
		RETURNS:		
		REMARKS:		Assuming .tga files, First layer tile data, Second layer tile Type data
	*/

	using namespace std;
	string line = "";
	int x, y, width, height, tileWidth, tileHeight;
	string tileFile = "";
	int *tilesRead = NULL;
	int *tileTypes = NULL;
	int tileIndex = 0;
	GLfloat tu, tv;

	// Opens a Flare map file .txt
	ifstream infile;
	infile.open(filename);

	getline(infile, line);
	if (!line.compare("[header]\n"))
	{
		cout << "Header information not found" << endl;
		return;
	}
	
	// Read Width
	getline(infile, line);
	line = line.substr(6);
	width = atoi(line.c_str());

	// Read Height
	getline(infile, line);
	line = line.substr(7);
	height = atoi(line.c_str());

	// Read Tile Width
	getline(infile, line);
	line = line.substr(10);
	tileWidth = atoi(line.c_str());

	// Read Tile Height
	getline(infile, line);
	line = line.substr(11);
	tileHeight = atoi(line.c_str());

	getline(infile, line); // Blank line

	// Read tileset filename Format: "./optionalFolder/filename.tga"
	getline(infile, line); // [tilesets]
	getline(infile, line);
	int start = line.find('.');
	int offset = start + 1;
	// Look for .. instead of .
	string nextChar = line.substr(offset, 1);
	if (nextChar.compare("."))
	{
	  offset++;
	  start++;
	}
	int end = line.find('.', offset+1);
	int extension = end - offset;
	line = line.substr(offset,extension);
	tileFile = line + ".tga";

	// Skip lines till 1st data
	do
	{
		getline(infile, line);
	}while (line.compare("data=") != 0);

	// Debug Checks
	if (0)
	{
		cout << "width = " << width << endl;
		cout << "heigth = " << height << endl;
		cout << "tileWidth = " << tileWidth << endl;
		cout << "tileHeight = " << tileHeight << endl;
		cout << "tileSet = " << tileFile << endl;
	}

	// Create array for tile data
	tilesRead = new int [width * height];

	// Read Data
	//while(!infile.eof())
	do
	{
		//getline(infile, line, ',');
		getline(infile, line);
		
		std::vector<string> tokens;
		stringstream ss(line);
		string token;
		
		while (std::getline(ss, token, ','))
			tokens.push_back(token);

		for (int i = 0; i < (int) tokens.size(); i++)
		{
			tilesRead[tileIndex] = atoi(tokens[i].c_str());
			tileIndex++;
			 
			// Debug Check
			if (0)
				cout << line << endl;
		}
	}while(line.compare("") != 0);
	//while(tileIndex < (width * height));
	
	// Skip lines till 2nd data
	do
	{
		getline(infile, line);
	}while (line.compare("data=") != 0 && !infile.eof());

	// Parse 2nd dataset as Tile Type
	if (!infile.eof())
	{
		tileTypes = new int[width * height];
		tileIndex = 0;

		do
		{
			//getline(infile, line, ',');
			getline(infile, line);
		
			std::vector<string> tokens;
			stringstream ss(line);
			string token;
		
			while (std::getline(ss, token, ','))
				tokens.push_back(token);

			for (int i = 0; i < (int) tokens.size(); i++)
			{	
				tileTypes[tileIndex] = atoi(tokens[i].c_str());
				tileIndex++;
			}
			 
			// Debug Check
			if (0)
				cout << line << endl;
		}while(tileIndex < (width * height));
	}

	// Debug Check all tiles read
	if (0)
	{
		for (int i = 0; i < width * height; i++)
			cout << "tile[" << i << "] = " << tilesRead[i] << endl;
		cout << "Tiles Read = " << tileIndex << endl;
	}

	// Load Tileset Texture
	int *tileMapWidth = new int;
	int *tileMapHeight = new int;
   GLuint* tileSet = new GLuint;
	//GLuint tileSet = glTexImageTGAFile(tileFile.c_str(), tileMapWidth, tileMapHeight);
   *tileSet = glTexImageTGAFile(tileFile.c_str(), tileMapWidth, tileMapHeight);

	// Load tiles to level
	tileIndex = 0;
	int tileMapRows = *tileMapHeight / tileHeight;
	int tileMapCols = *tileMapWidth / tileWidth;
	GLfloat tSizeX = (GLfloat) 1.0 / tileMapCols;
	GLfloat tSizeY = (GLfloat) 1.0 / tileMapRows;
	int typeOffset = (tileMapRows * tileMapCols);

	*level = TileLevel(width, height, tileWidth, tileHeight);

	for (int i = 0; i < height; i++) // Row
	{
		for (int j = 0; j < width; j++) // Column
		{
			// Find Row / Column texture coords
			int tilePos = tilesRead[tileIndex];
         int row = (tileMapRows-1) - ((tilePos-1) / tileMapCols); // Flip Y for UV coords
			int column = (tilePos-1) % tileMapCols;
         
         // offset for blank tile 0
         if (tilePos == 0)
         {
            column = 2;
            row = 11;
         }

         // Set texture coords
			tu = column * tSizeX;
			tv = row * tSizeY;

			// Convert to x,y coords
			x = j * tileWidth;
			y = i * tileHeight;


			Sprite* sprite = &Sprite(tileSet, x, y, tileWidth, tileHeight, tu, tv, tSizeX, tSizeY);
			
         // Load collidable tiles index
         if (tileTypes != NULL)
			{
				int type = tileTypes[tileIndex];
				if (type != 0)
				{
					type -= typeOffset;
					int index = level->tileArray.size();
					level->collidableTiles.push_back(index);

				}
				sprite->type = type;
			}
			level->tileArray.push_back(*sprite);
			tileIndex++;
		}
	}

	// Cleanup
	infile.close();
	delete[] tilesRead;
}