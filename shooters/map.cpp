/*
    author: Pham Francesco
    Alias: frankplus
    Email: binh282828@hotmail.it
*/
#include "map.h"
#include <cstdlib>

using namespace std;

map::map(string name)
{
    MapName = name;
    TileSheet = new ClassSurface("maps/"+MapName+"/tile.bmp"); //load TileSheet

    //init values
    int TileSheetWidth = TileSheet->GetWidth();
    int TileSheetHeight = TileSheet->GetHeight();
    if(TileSheetWidth % TILE_WIDTH == 0) TilesInX = TileSheetWidth / TILE_WIDTH;
    else PrintError(200);
    if(TileSheetHeight % TILE_HEIGHT == 0) TilesInY = TileSheetHeight / TILE_HEIGHT;
    else PrintError(201);

    //init collisions matrix
    collisions.resize(LIMITLINES);
    for(int i=0; i<LIMITLINES; i++)
        collisions[i].resize(LIMITPOINTSPERLINE);

    //init CollisionPeople matrix
    CollisionPeople.resize(LIMITLINES);
    for(int i=0; i<LIMITLINES; i++)
        CollisionPeople[i].resize(LIMITPOINTSPERLINE);

    clip = new SDL_Rect[TilesInX*TilesInY]; //allocate clip array

    //init clip array
    int z=0;
    for(int i=0; i<TilesInY; i++)
    {
        for(int j=0; j<TilesInX; j++,z++)
        {
            clip[z].x = TILE_WIDTH*j;
            clip[z].y = TILE_HEIGHT*i;
            clip[z].w = TILE_WIDTH;
            clip[z].h = TILE_HEIGHT;
        }
    }

}

map::~map()
{
    delete TileSheet; //deallocate tilesheet
    delete [] clip; //deallocate clip array
}

void map::load()
{
    //load map.txt
    string path = "maps/"+MapName+"/map.txt";
    ifstream MapTxt(path.c_str());
    if(!MapTxt || !MapTxt.is_open()) PrintError(202);
    string line;

    char buffer[512];
    bool success=true;

    //load background
    do
    {
        MapTxt.getline(buffer,512);

        if(MapTxt.eof() || MapTxt.fail())
        {
            success = false;
            break;
        }
        line = buffer;
    }while(line.compare("info {") != 0);

    if(!success)
    {
        bgType = 0;
        MapTxt.clear();
        MapTxt.seekg(0);
    }
    else
    {
        do
        {
            MapTxt.getline(buffer,512);
            line = buffer;
            if(line[0]=='b' && line[1]=='g' && line[2]==':')
            {
                for(int i=0; i<8; i++)
                {
                    if(line[i+3]>='1' && line[i+3]<='9') buffer[i] = line[i+3];
                    else
                    {
                        buffer[i] = '\0';
                        break;
                    }
                }
                bgType = atoi(buffer);
            }
        }while(line.compare("}") != 0);
    }

    // Work out the width and height
    do
    {
        MapTxt.getline(buffer,512);
        if(MapTxt.eof() || MapTxt.fail()) PrintError(203);
        line = buffer;
    }while(line.compare("tiles {") != 0);

    width = -1 ;
    height = 0 ;
    do
    {
        MapTxt.getline(buffer,512);
        line = buffer;
        if(width == -1)
        {
            width = 1;
            for(unsigned int i=0; i<line.length(); i++)
            {
                if(line[i] == ',') width++;
            }
        }
        height++;
    }while(line.compare("}") != 0);
    height--; // don't include the "}" line

    //rewind the stream
    MapTxt.seekg(0);

    //allocazione dinamica della matrice contenente la mappa
    TileTypes = new int*[width];
    for(int i=0; i<width; i++) TileTypes[i] = new int[height];

    //load tiles
    do
    {
        MapTxt.getline(buffer,512);
        if(MapTxt.eof() || MapTxt.fail()) PrintError(204);
        line = buffer;
    }while(line.compare("tiles {") != 0);

    int temp;
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            line = "";
            for(int z=0; z<8; z++)
            {
                temp = MapTxt.get();
                if(temp != ',' && temp != '\0' && temp != '\n')
                {
                    if(temp<'0' || temp>'9') PrintError(205);
                    line += temp;
                }
                else
                {
                    if((temp=='\0' || temp=='\n') && j<width-1) PrintError(206);
                    temp = atoi(line.c_str()); //riutilizzo di temp
                    //if(temp == 0) PrintError(207); doesn't work
                    TileTypes[j][i] = temp;
                    break;
                }
            }
        }
    }

    //move to collisions
    do
    {
        MapTxt.getline(buffer,512);
        if(MapTxt.eof() || MapTxt.fail()) PrintError(208);
        line = buffer;
    }while(line.compare("collision {") != 0);

    //get collisions
    for(int i=0; i<LIMITLINES; i++)
    {
        temp = MapTxt.get();
        if(temp == '}')
        {
            collisions.resize(i);
            break;
        }

        for(int j=0; j<LIMITPOINTSPERLINE; j++)
        {
            if(temp != '(') PrintError(209);

            //x coordinate
            for(int z=0; z<256; z++)
            {
                temp = MapTxt.get();
                if(temp>='0' && temp<='9') buffer[z] = temp;
                else
                {
                    buffer[z] = '\0';
                    collisions[i][j].x = atoi(buffer)*zoom;
                    break;
                }
            }
            if(temp != ',') PrintError(210);

            //y coordinate
            for(int z=0; z<256; z++)
            {
                temp = MapTxt.get();
                if(temp>='0' && temp<='9') buffer[z] = temp;
                else
                {
                    buffer[z] = '\0';
                    collisions[i][j].y = atoi(buffer)*zoom;
                    break;
                }
            }
            if(temp != ')') PrintError(211);

            //check if the line is ended
            temp = MapTxt.get();
            if(temp != ',')
            {
                collisions[i].resize(j+1);
                break;
            }
            temp = MapTxt.get(); //for start the next cicle
        }
    }


    //move to CollisionPeople
    success = true;
    do
    {
        MapTxt.getline(buffer,512);
        if(MapTxt.eof() || MapTxt.fail())
        {
            success = false;
            break;
        }
        line = buffer;
    }while(line.compare("collisionPeople {") != 0);

    //get collisions
    if(success)
    {
        for(int i=0; i<LIMITLINES; i++)
        {
            temp = MapTxt.get();
            if(temp == '}')
            {
                CollisionPeople.resize(i);
                break;
            }

            for(int j=0; j<LIMITPOINTSPERLINE; j++)
            {
                if(temp != '(') PrintError(213);

                //x coordinate
                for(int z=0; z<256; z++)
                {
                    temp = MapTxt.get();
                    if(temp>='0' && temp<='9') buffer[z] = temp;
                    else
                    {
                        buffer[z] = '\0';
                        CollisionPeople[i][j].x = atoi(buffer)*zoom;
                        break;
                    }
                }
                if(temp != ',') PrintError(214);

                //y coordinate
                for(int z=0; z<256; z++)
                {
                    temp = MapTxt.get();
                    if(temp>='0' && temp<='9') buffer[z] = temp;
                    else
                    {
                        buffer[z] = '\0';
                        CollisionPeople[i][j].y = atoi(buffer)*zoom;
                        break;
                    }
                }
                if(temp != ')') PrintError(215);

                //check if the line is ended
                temp = MapTxt.get();
                if(temp != ',')
                {
                    CollisionPeople[i].resize(j+1);
                    break;
                }
                temp = MapTxt.get(); //for start the next cicle
            }
        }
    }
    else //if success == false
    {
        CollisionPeople.clear();
        MapTxt.clear();
        MapTxt.seekg(0);
    }

    //;move to spawns
    do
    {
        MapTxt.getline(buffer,512);
        if(MapTxt.eof() || MapTxt.fail()) PrintError(216);
        line = buffer;
    }while(line.compare("spawns {") != 0);

    spawn TempSpawn;

    //load spawns
    for(;;)
    {
        if(MapTxt.get() != '(') PrintError(217);

        //get team (CT or TT)
        for(int i=0;;i++)
        {
            temp = MapTxt.get();
            if(temp == ',')
            {
                buffer[i] = '\0';
                break;
            }
            else buffer[i] = temp;
        }
        TempSpawn.team = atoi(buffer);

        //get x position
        for(int i=0;;i++)
        {
            temp = MapTxt.get();
            if(temp == ',')
            {
                buffer[i] = '\0';
                break;
            }
            else buffer[i] = temp;
        }
        TempSpawn.Xpos = atoi(buffer)*zoom;

        //get y position
        for(int i=0;;i++)
        {
            temp = MapTxt.get();
            if(temp == ')')
            {
                buffer[i] = '\0';
                break;
            }
            else buffer[i] = temp;
        }
        TempSpawn.Ypos = atoi(buffer)*zoom;

        TempSpawn.free = true;
        SpawnsArr.push_back(TempSpawn);
        if(MapTxt.get() != ';') break;
    }

    MapTxt.close();
}

//print map on screen
void map::print(SDL_Surface *screen, SDL_Rect camera)
{
    int type;
    camera.x += ExtraMap*TILE_WIDTH;
    camera.y += ExtraMap*TILE_HEIGHT;

    for(int i=0; i<height+ExtraMap*2; i++)
    {
        for(int j=0; j<width+ExtraMap*2; j++)
        {
            SDL_Rect box = {TILE_WIDTH*j, TILE_HEIGHT*i, TILE_WIDTH, TILE_HEIGHT};
            //If the tile is on screen
            if( InCamera(camera, box) == true )
            {
                //Show the tile
                TileSheet->move(box.x - camera.x, box.y - camera.y);
                if(i<ExtraMap || i>=height+ExtraMap || j<ExtraMap || j>=width+ExtraMap) type = bgType;
                else type = TileTypes[j-ExtraMap][i-ExtraMap];
                TileSheet->blit(screen,&clip[type]);
            }
        }
    }
}

bool map::InCamera( SDL_Rect A, SDL_Rect B )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB ) return false;
    if( topA >= bottomB ) return false;
    if( rightA <= leftB ) return false;
    if( leftA >= rightB ) return false;

    //If none of the sides from A are outside B
    return true;
}

bool map::CheckCollisionMap(int posX, int posY, int radius, bool people)
{
    bool ret;
    point C;
    C.x = posX;
    C.y = posY;

    //for people and bullets
    for(unsigned int i=0; i<collisions.size(); i++)
    {
        for(unsigned int j=0; j<collisions[i].size()-1; j++)
        {
            ret = CheckCollision(collisions[i][j], collisions[i][j+1], C, radius);
            if(ret) return true;
        }
    }

    //only people
    if(people)
    {
        for(unsigned int i=0; i<CollisionPeople.size(); i++)
        {
            for(unsigned int j=0; j<CollisionPeople[i].size()-1; j++)
            {
                ret = CheckCollision(CollisionPeople[i][j], CollisionPeople[i][j+1], C, radius);
                if(ret) return true;
            }
        }
    }
    return false;
}

spawn map::GetPosSpawn(int team)
{
    unsigned int i;

    //find a free and team spawn
    for(i=0; i<SpawnsArr.size(); i++)
        if(SpawnsArr[i].free==true && SpawnsArr[i].team==team)
            return SpawnsArr[i];

    //if no one is free
    for(i=0; i<SpawnsArr.size(); i++)
        if(SpawnsArr[i].team==team)
            return SpawnsArr[i];

    //else
    return SpawnsArr[0];
}
