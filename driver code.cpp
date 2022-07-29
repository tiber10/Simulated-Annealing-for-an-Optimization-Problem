#include <bits/stdc++.h>

using namespace std;

class SimulatedAnnealing{
    protected:
    int numstu = 200,numroo = 50,stuperRoom = 4,InitialTemperature = 2000,changeAcc,BEST, WORST,AVERAGE,swappingatt;
    double reduction = 0.99,temperature;
    bool solved;
    int FitSCORE[50];
    int rooms[200];
    int stucomp[40000];

    public:
    SimulatedAnnealing(int stucomp[]){
        for(int i=0;i<40000;i++){
            this->stucomp[i] = stucomp[i];
        }
        temperature = InitialTemperature;
        swappingatt = 0;
        changeAcc = 0;
        BEST = 0;
        WORST = 0;
        AVERAGE = 0;
        solved = false;
        srand(time(NULL));
        //Assigning
        for (int i = 0; i < numroo*stuperRoom; i++){
            rooms[i] = i;
        }
        for (int i = 0; i < numroo; i++){
            FitSCORE[i] = calcFitness(i);
        }
    }

    //Calculating the fitness score
    int calcFitness(int roomCounter){
        int score = 0;
        for (int i = 0; i < stuperRoom; i++){
            for (int j = i+1; j < stuperRoom; j++){
                int row = roomCounter*stuperRoom + i;
                int col = roomCounter*stuperRoom + j;
                score += stucomp[rooms[row]*200 + rooms[col]];
            }
        }
        return score;
    }
    //choosing random rooms than swapping students
    void swapping(){
        int randRo1 = rand() % 50+0, randRo2 = rand() % 50+0;
        int initFit = 0,randFit = 0;
        initFit +=  calcFitness(randRo1);
        initFit +=  calcFitness(randRo2);
        if (randRo1 == randRo2){
            swapping();
        }
        else {
            int ranStu1 = rand() % 4+0;
            int ranStu2 = rand() % 4+0;
            int temp = rooms[(randRo1*stuperRoom) + ranStu1];
            rooms[(randRo1*stuperRoom) + ranStu1] = rooms[(randRo2*stuperRoom) + ranStu2];
            rooms[(randRo2*stuperRoom) + ranStu2] = temp;
            swappingatt++;
            randFit += calcFitness(randRo1);
            randFit += calcFitness(randRo2);
            if(swapAcc(initFit,randFit)){
                changeAcc++;
                FitSCORE[randRo1] = calcFitness(randRo1);
                FitSCORE[randRo2] = calcFitness(randRo2);
            }
            else{
                temp = rooms[(randRo2*stuperRoom) + ranStu2];
                rooms[(randRo2*stuperRoom) + ranStu2] = rooms[(randRo1*stuperRoom) + ranStu1];
                rooms[(randRo1*stuperRoom) + ranStu1] = temp;
            }
        }
    }
    //this is the random swap where you take a random room and swap the first two students with the last
    void unifSwapping(){
        int randRo1 = rand() % 50+0;
        int randRo2 = rand() % 50+0;
        int initFit = 0;
        int randFit = 0;
        initFit +=  calcFitness(randRo1);
        initFit +=  calcFitness(randRo2);
        if (randRo1 == randRo2){
            unifSwapping();
        }
        else{
            int ts1, ts2;
            ts1 = rooms[(randRo1*stuperRoom) + 0];
            ts2 = rooms[(randRo1*stuperRoom) + 1];
            rooms[(randRo1*stuperRoom) + 0] = rooms[(randRo2*stuperRoom) + 2];
            rooms[(randRo1*stuperRoom) + 1] = rooms[(randRo2*stuperRoom) + 3];
            rooms[(randRo2*stuperRoom) + 2] = ts1;
            rooms[(randRo2*stuperRoom) + 3] = ts2;
            swappingatt++;
            randFit += calcFitness(randRo1);
            randFit += calcFitness(randRo2);
            if(swapAcc(initFit,randFit)){
                changeAcc++;
                FitSCORE[randRo1] = calcFitness(randRo1);
                FitSCORE[randRo2] = calcFitness(randRo2);
            }
            else{
                ts1 = rooms[(randRo2*stuperRoom) + 2];
                ts2 = rooms[(randRo2*stuperRoom) + 3];
                rooms[(randRo2*stuperRoom) + 2] = rooms[(randRo1*stuperRoom) + 0];
                rooms[(randRo2*stuperRoom) + 3] = rooms[(randRo1*stuperRoom) + 1];
                rooms[(randRo1*stuperRoom) + 0] = ts1;
                rooms[(randRo1*stuperRoom) + 1] = ts2;
            }
        }
    }
    //checking if the swap is good
    bool swapAcc(int initial, int final){
        double probabilityAccept = 0.0;
        int floor = 0;
        int ceiling = 1;
        double randomToAccept = floor + (double)(rand())/((double)(RAND_MAX/(ceiling - floor)));
        if(final <= initial){
            return true;
        }
        probabilityAccept = exp((initial - final)/temperature);
        if (probabilityAccept >= randomToAccept){
            return true;
        }
        return false;
    }

    //solve method runs until reduce temperature criteria is fulfilled
    void Solve(){
        while(!solved){
            // picking randomly swap
            int pick = rand() % 2;
            if(pick == 0){
                unifSwapping();
            }
            else
                swapping();
            // here im going to reduce temperature
            if((swappingatt >= 20000) || (changeAcc >= 2000)){
                if (changeAcc == 0){
                    cout<<"Problem SOLVED !! \n";
                    solved = true;
                    return;
                }
                swappingatt = 0;
                changeAcc = 0;
                temperature *= reduction;
            }
        }
        for (int i = 0; i < 200; i++){
             SortFileAndInfo(i);
        }
        outputResult();
    }


    //sorting the results
    void SortFileAndInfo(int roomCounter){
        BEST = FitSCORE[0];
        WORST = FitSCORE[0];
        for(int i = 0; i < 50; i++){
            if(FitSCORE[i] < BEST){
                BEST = FitSCORE[i];
            }
            if(FitSCORE[i] > WORST){
                WORST = FitSCORE[i];
            }
            AVERAGE += FitSCORE[i];
        }
        AVERAGE = AVERAGE/50;
        int temp;
        for (int i = 0; i < stuperRoom; i++){
            for (int j = i+1; j < stuperRoom; j++){
                if (rooms[(stuperRoom*roomCounter)+i] > rooms[(stuperRoom*roomCounter)+j]){
                    temp = rooms[(stuperRoom*roomCounter)+i];
                    rooms[(stuperRoom*roomCounter)+i] = rooms[(stuperRoom*roomCounter)+j];
                    rooms[(stuperRoom*roomCounter)+j] = temp;
                }

            }
        }
    }

    // Write the output results in file
    void outputResult(){
        ofstream outputFile;
        outputFile.open("test1.txt");
        outputFile << "We Start with Temperature: " << InitialTemperature << setw(8) << "\n"
            << "Reduction: " << setw(8) << reduction << "\n"
            << "Best Compatibility: "<< setw(8) << BEST << "\n"
            << "Worst Compatibility: " << setw(8)<< WORST << "\n"
            << "Average Compatibility: " << setw(4) << AVERAGE << "\n\n";
        for (int i = 0; i < numroo; i++){
            outputFile << "Room " << i << ": " << rooms[i*stuperRoom]
            << " | " << rooms[i*stuperRoom +1]
            << " | " << rooms[i*stuperRoom +2]
            << " | " << rooms[i*stuperRoom +3]
            << " Fitness Score: " <<  FitSCORE[i] << "\n";
        }
    }

};

// rInp = Room Mates Input file
// stucomp = student compatibility matrix
int main(){
    ifstream rInp;
    rInp.open("roommates.txt");
    int stucomp[40000];
    if (!rInp){
        return -1;
    }
    for (int i = 0; i < 40000; i++){
        rInp >> stucomp[i];
    }
    SimulatedAnnealing simanneal(stucomp);

    simanneal.Solve();
    return 0;
}

