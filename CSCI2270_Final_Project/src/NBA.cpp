#include "NBA.h"

using std::cout;
using std::endl;

NBA::NBA()
{
    nil = new BasketballTeams();
    nil->isRed = false;
    root = nil;
}

NBA::~NBA()
{
    //dtor
}

void NBA::addTeam(std::string tName, std::string pName, int number, std::string position, int played, int points, int rebounds, int steals, int assists, int turnovers, int fouls)
{
    /*for(int i = 0; i<teamNameVector.size(); i++)
    {
        std::cout<<teamNameVector[i];
    }
    std::cout<<std::endl;*/
    //cout<<"x"<<endl;
    BasketballPlayer *player = new BasketballPlayer(pName, number, position, played, points, rebounds, steals, assists, turnovers, fouls);
    bool added = false;
    BasketballTeams *rootTemp = root;
    BasketballTeams *team;
    if(!(searchVector(tName)))
    {
        teamNameVector.push_back(tName);
        team = new BasketballTeams(tName);
        team->left = nil;
        team->right = nil;
        if(root == nil)
        {
            team->parent = nil;
            root = team;
        }
        else
        {
            while(!added)
            {
                if(team->strName.compare(rootTemp->strName) < 0)
                {
                    if(rootTemp->left == nil)
                    {
                        rootTemp->left = team;
                        team->parent = rootTemp;
                        added = true;
                    }
                    else
                    {
                        rootTemp = rootTemp->left;
                    }
                }
                else
                {
                    if(rootTemp->right == nil)
                    {
                        rootTemp->right = team;
                        team->parent = rootTemp;
                        added = true;
                    }
                    else
                    {
                        rootTemp = rootTemp->right;
                    }
                }
            }
        }
        rbAddFixup(team);
    }
    //cout<<"x"<<endl;
    team = searchTree(tName);
    team->vecPlayers.push_back(player);
    //cout<<"x"<<endl;
}

void NBA::rbAddFixup(BasketballTeams *x)
{
    cout<<"x"<<endl;
    x->left = nil;
    x->right = nil;
    x->isRed = true;
    while ( (x != root) && (x->parent->isRed == true) )
    {
        if (x->parent == x->parent->parent->left)
        {
            cout<<"x"<<endl;
            /* If x's parent is a left, y is x's right 'uncle' */
            BasketballTeams *y = x->parent->parent->right;
            if (y->isRed == true)
            {
                /* case 1 - change the colors */
                x->parent->isRed = false;
                y->isRed = false;
                x->parent->parent->isRed = true;
                /* Move x up the tree */
                x = x->parent->parent;
            }
            else
            {
                /* y is a black node */
                if (x == x->parent->right)
                {
                    /* and x is to the right */
                    /* case 2 - move x up and rotate */
                    x = x->parent;
                    leftRotate(x);
                }
                /* case 3 */
                x->parent->isRed = false;
                x->parent->parent->isRed = true;
                rightRotate(x->parent->parent);
            }
        }
        else
        {
            cout<<"y"<<endl;
            /* If x's parent is a left, y is x's right 'uncle' */
            BasketballTeams *y = x->parent->parent->left;
            if ( y->isRed == true)
            {
                cout<<"x"<<endl;
                /* case 1 - change the colors */
                x->parent->isRed = false;
                y->isRed = false;
                x->parent->parent->isRed = true;
                /* Move x up the tree */
                x = x->parent->parent;
            }
            else
            {
                cout<<"y"<<endl;
                /* y is a black node */
                if ( x == x->parent->left)
                {
                    /* and x is to the right */
                    /* case 2 - move x up and rotate */
                    x = x->parent;
                    rightRotate(x);
                }
                /* case 3 */
                x->parent->isRed = false;
                x->parent->parent->isRed = true;
                leftRotate(x->parent->parent);
            }
        }
    }
    /* Color the root black */
    root->isRed = false;
}

void NBA::leftRotate(BasketballTeams *x)
{
    BasketballTeams *w = x->right;
    x->right = w->left;
    if(w->left != nil)
    {
        w->left->parent = x;
    }
    w->parent = x->parent;
    if(x->parent == nil)
    {
        root = w;
    }
    else if(x == x->parent->left)
    {
        x->parent->left = w;
    }
    else
    {
        x->parent->right = w;
    }
    w->left = x;
    x->parent = w;
}

void NBA::rightRotate(BasketballTeams *x)
{
    BasketballTeams *w = x->left;
    x->left = w->right;
    if(w->right != nil)
    {
        w->right->parent = x;
    }
    w->parent = x->parent;
    if(x->parent == nil)
    {
        root = w;
    }
    else if(x == x->parent->left)
    {
        x->parent->left = w;
    }
    else
    {
        x->parent->right = w;
    }
    w->right = x;
    x->parent = w;
}

BasketballTeams* NBA::searchTree(std::string tName)
{
    BasketballTeams *rootTemp = root;
    while(rootTemp != nil)
    {
        if(rootTemp->strName == tName)
        {
            return rootTemp;
        }
        else
        {
            if(tName.compare(rootTemp->strName) < 0)
            {
                rootTemp = rootTemp->left;
            }
            else
            {
                rootTemp = rootTemp->right;
            }
        }
    }
    return rootTemp;
}

bool NBA::searchVector(std::string tName)
{
    bool found = false;
    for(int i = 0; i<teamNameVector.size(); i++)
    {
        if(teamNameVector[i] == tName)
        {
            found = true;
            break;
        }
    }
    return found;
}

void NBA::printTeams()
{
    printTeams(root);
}

void NBA::printTeams(BasketballTeams *rootTemp)
{
    if(rootTemp->left != nil)
    {
        printTeams(rootTemp->left);
    }
    std::cout<<"Team: "<<rootTemp->strName<<std::endl;
    if(rootTemp->right != nil)
    {
        printTeams(rootTemp->right);
    }
}
