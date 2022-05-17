/*
Description: Using class and pointers to run a battle ship 
style game in whihc grid points are replaced with selctions
based on pointer. Accounting for memory leakes ussing null
terminators     
Input:there is no imputfile for this code 
Output: the out put presents a grid with arm, art, and inf
to show the possible scenarious. in addiotion to that, it 
tells you what was destroyed and what wasnt based on the 
points of the grid that have changed 
*/

#include<iostream>
#include <cstdlib>
using namespace std;

//Superclass, keeps track of name 
class ent_t {
  public:
    ent_t(string n = "None") : id(ent_cnt++) {
        name=new string;
       *name = n; 
        //Your Code Here
    }
    ~ent_t(){ 
        if(name!=NULL){
            delete name;
        }
        name = NULL;  
        /*Your Code Here*/
        } //Destructor
    ent_t(const ent_t &old){ //Copy Constructor
        name=new string;
        //old.getName();
        *name = *(old.name); 
        //Your Code Here (copy constructor code here)
        id = ent_cnt++; //don't copy old id, just keep increasing it.
    }
    void setName(string n){
        if(name == NULL){
            name=new string; 
            *name= n;
        }
        else {
            *name= n;  
        } 
    }
    string getName() const {
        
        return *name; 
    }
    //Your code here for void setName and string getName
    int getID() const {return id;}

  protected:
    string *name;
    int id;
    static int ent_cnt;
};
int ent_t::ent_cnt = 0; //initialize static

class infantrySquad_t : public ent_t {
  public:
  //worked on 
  infantrySquad_t(string name="Infantray Squad"):ent_t(name){}
    //Your code here for constructor, 
    //call ent_t and pass name. Use default "Infantry Squad"
};

class armorSquad_t : public ent_t {
  public:
    armorSquad_t(string name = "Armor Squad") : ent_t(name) {

    }
};

class artillerySquad_t : public ent_t {
  public:
    artillerySquad_t(string name = "Artillery Squad") : ent_t(name) {

    }
};

//Class to represent each point on the map and what it holds.
// Can hold up to 1 armor and artillery squad,
//but can also hold a variable amount of infantry squads (dynamic array)
class point_t {
  public:
    point_t(int x = 0, int y = 0) : arm(NULL), art(NULL),
     inf(NULL), x(x), y(y) {}
    ~point_t() { 
        if(arm != NULL){
           delete arm;
            arm=NULL;
        }
        if(art != NULL){
            delete art; 
            art=NULL;
        }
       
        if(inf != NULL){
           int i = 0; 
            while(inf[i]!=NULL)
            {
                delete inf[i];
                i++; 
            } 
            delete[] inf;
            inf = NULL; 
        } 
        //Cleanup all the pointers. also de-allocate the inf array
        //Your Code Here
        x=0;
        y=0;
    }
    void print(){
        cout << "Point (" << x << ", " << y << ") contains:\n";
        if(arm != NULL){
            cout << arm->getName()<<endl;    
            //Your Code Here for couting using getName() in art
        } 
        if(art!= NULL){
            cout << art->getName()<<endl; 
        //Your code here, same for art.
        }
        //infantrySquad_t ** temp= inf;
        if(inf != NULL){
            // infantrySquad_t** temp = inf;
            // while(*temp != NULL){
            //     cout << (*temp)->getName() << ", ";
            //     temp++; 
            // }
            int i=0; 
            //infantrySquad_t** temp = inf;
            while(inf[i] != NULL){
                cout << inf[i]->getName() << ", ";
                i++; 
            }
            cout << endl; 
           //infantrySquad_t ** temp= inf;
            // int i=0; 
            // while(inf[i]!=NULL){
            //     cout<< inf[i]->getName()<<", "; 
            //     inf++;
            //     i++; 
            // }
            // cout<< endl; 
            //Your Code Here
            //loop to print the array. The inf array MUST 
            //be null terminated or this breaks!
        }
    }
    char getChar(){
            if(arm == NULL && art == NULL && inf == NULL) return '0';
             if(arm == NULL && art ==NULL && inf != NULL) return 'I';
             if(arm == NULL && art !=NULL && inf == NULL) return 'A';
             if(arm == NULL && art !=NULL && inf != NULL) return 'D';
             if(arm != NULL && art ==NULL && inf == NULL) return 'T';
             if(arm != NULL && art ==NULL && inf != NULL) return 'C';
             if(arm != NULL && art !=NULL && inf == NULL) return 'B';
             if(arm != NULL && art !=NULL && inf != NULL) return '!';
            return 'G'; 
        //Your Code here, add the rest of the characters
        //I A D T C B !
    }
    string getInfantryCount(){
        if(inf == NULL) return "  ";
        int count = 0; 
           
            while(inf[count]!=NULL){
                count++; 
            }
        //Your Code Here
        //     cout<< inf[i]->getName()<<", "; 
            //     inf++;
            //     i++; 
            // }
            // cout<< endl; 
            //Your Code Here
            //loop to print the array. The inf array MUST 
            //be null terminated or this breaks!
        return to_string(count);
    }
    armorSquad_t*     arm;
    artillerySquad_t* art;
    infantrySquad_t**   inf;
    int x;
    int y;
};


//Holds map, adds and removes entities
class map_t {
  public:
    map_t(int x = 10, int y = 9) : x(x), y(y) {
       //to draw the grid 
        point=new point_t*[y]; 
        for(int i= 0; i < y; i++){
            point[i]= new point_t[x];
        for(int j = 0; j < x; j++) {
            point[i][j].x=j; 
            point[i][j].y=i;
        }

      }
        //map is y and then x 
        //Your Code Here DO THIS FIRST
        loadData();
    }
    ~map_t(){ //cleanup
        //Your Code Here DO THIS SECOND
        if(point != NULL){   
            for(int i= 0; i < y; i++){
                delete [] point[i];   
            }
            delete [] point;
            point = NULL; 
        }
    }
    void draw();
    void attackMove(point_t* origin, point_t* dest){
        
        if(origin->arm == NULL)
        {
            cout << "No armor available.\n";
        }
        else {
            cout<<origin->arm->getName() 
            << " moving to ("<<dest->x<<", "<<dest->y<< ")\n";
            cout << "Destroyed "<< dest->arm->getName()<<endl; 
            //delete dest ->arm;
            //origin->arm=NULL; 
                         
            delete dest ->arm;
            dest->arm=origin->arm; 
            //cout << "Destroyed AT-ATs" << endl; 
            //delete origin->arm;
            origin->arm=NULL;
        } 
        //Your Code Here
    }
    //Fires at a point, destroys everything there.
    void fireAt(point_t *origin, point_t *target){
        //to fire at the point 
        cout<< origin->art->getName();
        cout<< " Fires at ("<<target->x<<", "<<target->y<<")!!!\n"; 
        target->print();
        cout<<"All units destroyed!\n"; 
        //the disctricutr 
        target->~point_t();
        //going after the art 
        if (target->art)
        {
            delete target->art;
            target->art=NULL;
        }
        //going after the arm 
        if(target->arm)
        {
            delete target->arm;
            target->arm=NULL; 
        } 
       //going after the inf 
        if(target->inf)
        {
            int i =0;
            while(target->inf[i] != NULL)
            {
                delete[] target->inf[i]; 
                i++; 
            }
            delete[] target->inf;
            target->inf=NULL; 
        }
        
        //Your Code Here
    }
    void addInfantry(point_t* location, int amount,
                     const string &n = "501st Infantry Squad ")
                     { //add + 1 for the null spot
        
        if(location->inf == NULL){
            location->inf=new infantrySquad_t*[amount+1];
            location->inf[amount]=NULL;
            for(int i = 0; i < amount; i++)
            {
                location->inf[i]=new infantrySquad_t(n+to_string(i+1));
                
            }       
                  
            //Your Code Here
        }
        else{ //deep copy practice
            //Your Code Here  
            int count=0; 
            infantrySquad_t** empTemp=location->inf; //works 
            while(*empTemp!=NULL){
                empTemp++;//works 
                count++; //works 
            }//new temp
    infantrySquad_t** tempArray=new infantrySquad_t*[count + amount + 1];
            tempArray[amount + count]=NULL;
            for(int i = 0; i <count; i++){
                tempArray[i]=location->inf[i]; //works 
            }
            //copy done as well to work 
            for(int i= 0; i < amount+count; i++){
                tempArray[i]=new infantrySquad_t(n+to_string(i+1));
            }
            //deallocate
            //location->inf[count+amount+1]=NULL; 
            delete [] location->inf; 
            location->inf=tempArray;
        }
    }//done 
    point_t** point;
  private:
    void loadData();
    int x;
    int y;
};

void map_t::draw(){
    //Your Code Here 
    // point=new point_t*[y]; 
    
    for(int i=0; i < y; i++){
        for(int j=0; j < x; j++){
            //point[i][j].x=j; 
            //point[i][j].y=i;
            cout << point[i][j].getChar()
            //if(point[i][j].inf!=NULL){ 
            << point[i][j].getInfantryCount();
            //}
            //else 
            //cout<< "   "; 
            if(j<x-1){
                cout<<" ";
            }
       }
       cout << endl; 
    }
    cout << endl;
}

void map_t::loadData(){
    cout << "The First Order is the best order..." << endl;
}

int main(int argc, char *argv[]) {
    map_t *Crait = new map_t;
    //The First Order
    Crait->addInfantry(&Crait->point[2][8], 13, "Stormtrooper Squads");
    Crait->addInfantry(&Crait->point[2][6], 22, "Stormtrooper Squads");
    Crait->point[1][7].arm = new armorSquad_t("AT-ATs");
    Crait->point[1][5].arm = new armorSquad_t("AT-ATs");
    Crait->point[8][6].arm = new armorSquad_t("AT-ATs");
    Crait->addInfantry(&Crait->point[8][6], 11, "Stormtrooper Squads");
    Crait->point[4][8].art = new artillerySquad_t("AT-MA");
    Crait->point[6][8].art = new artillerySquad_t("AT-MA");
    Crait->point[6][8].arm = new armorSquad_t("AT-ATs");
    Crait->addInfantry
    (&Crait->point[6][8], 11, "Kylo Ren's Private Army");
    Crait->addInfantry(&Crait->point[7][8], 33, "Stormtrooper Squads");
    Crait->point[7][8].art = new artillerySquad_t("AT-MA");
    Crait->addInfantry(&Crait->point[8][6], 14, "Stormtrooper Squads");
     //MOAARRR
    //The Resitance
    Crait->point[6][2].art = new artillerySquad_t();
    Crait->point[6][2].arm = new armorSquad_t();
    Crait->point[4][2].arm = new armorSquad_t("Speeders");
    Crait->addInfantry(&Crait->point[5][3], 22, "The Resistance");
    Crait->point[1][4].arm = new armorSquad_t("Speeders");
    Crait->point[2][3].art = new artillerySquad_t("Damaged Artillery");
    Crait->point[2][3].arm = new armorSquad_t
    ("Some rusty tanks acting as decoys");
    Crait->addInfantry
    (&Crait->point[2][3], 12, "Decoy Resistance Soldiers");
    Crait->draw();
    //The Action!
    Crait->attackMove(&Crait->point[2][4], &Crait->point[1][5]);
    Crait->attackMove(&Crait->point[1][4], &Crait->point[1][5]);
    Crait->fireAt(&Crait->point[4][8], &Crait->point[2][3]);
    Crait->draw();
    delete Crait; //lol
    return 0;
}
