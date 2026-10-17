#include <iostream>
#include <exception>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

class Igrac {
protected:
    int total;
    int aces;
    string name;
public:
    Igrac(string n = "") {
        name = n;
        total = 0;
        aces = 0;
    }

    virtual ~Igrac() {}

    int getTotal() const {
        return total;
    }

    void dodadiKarta(int value) {
        if (value == 1) {
            aces++;
            total += 11;
        } else {
            if (value >= 11) value = 10;
            total += value;
        }

        while (total > 21 && aces > 0) {
            total -= 10;
            aces--;
        }
    }

    virtual void display() const {
        cout << name << " total: " << total << endl;
    }
};

class Korisnik : public Igrac {
public:
    Korisnik(string n = "Player") : Igrac(n) {}

    void display() const override {
        cout << "Your total in cards: " << total << endl;
    }
};

class Diler : public Igrac {
public:
    Diler(string n = "Dealer") : Igrac(n) {}

    void display() const override {
        cout << "Dealer shows: " << total << endl;
    }
};

class Blackjack {
public:
    int vleciKarta() {
        return rand() % 13 + 1;
    }

    string sign(){
        int s = rand() % 4;
        if(s==0) return "♥";
        if(s==1) return "♦";
        if(s==2) return "♣";
        return "♠";
    }

    void pravila() {
        char izbor;
        cout << "Would you like to read the Blackjack rules? Enter 'y' for yes or 'n' for no: ";
        cin >> izbor;

        if (izbor == 'y') {
            cout << "\n--- BLACKJACK RULES ---\n";
            cout << "1. Your goal is to get as close to 21 as possible without going over.\n";
            cout << "2. Number cards are worth their face value.\n";
            cout << "3. Face cards (J, Q, K) are worth 10.\n";
            cout << "4. Aces can be worth 1 or 11.\n";
            cout << "5. Hit or Stand.\n";
            cout << "6. Dealer draws until 17.\n\n";
        }
        else if (izbor != 'n') {
            throw invalid_argument("Invalid input!");
        }
    }

    void pobednik(Igrac& p, Igrac& d) {
        cout << "\n---RESULT---\n";
        cout << "Your total: " << p.getTotal() << endl;
        cout << "Dealer total: " << d.getTotal() << endl;

        if (p.getTotal() > 21)
            cout << "You busted! Dealer wins.\n\n";
        else if (d.getTotal() > 21)
            cout << "Dealer busts! You win.\n\n";
        else if (p.getTotal() > d.getTotal())
            cout << "You win!\n\n";
        else if (d.getTotal() > p.getTotal())
            cout << "Dealer wins!\n\n";
        else
            cout << "It's a tie!\n\n";
    }

    bool IgrajPak() {
        char izbor;
        cout << "\n\nWould you like to play again? Enter 'y' for yes or 'n' for no: ";
        cin >> izbor;

        if (izbor != 'y' && izbor != 'n')
            throw invalid_argument("Invalid input!");

        return izbor == 'y';
    }

    void play() {
        Korisnik player;
        Diler dealer;

        cout << "\n---WELCOME TO BLACKJACK---\n\n";
        pravila();

        for(int i=0;i<2;i++){
            int k = vleciKarta();
            string znak = sign();
            cout<<"You drew: "<<(k>=11?10:k)<<znak<<endl;
            player.dodadiKarta(k);
        }

        int dk = vleciKarta();
        string dz = sign();
        cout<<"Dealer drew: "<<(dk>=11?10:dk)<<dz<<endl;
        dealer.dodadiKarta(dk);

        cout << endl;
        player.display();
        dealer.display();

        char izbor;

        do{
            cout<<"\nIf you want to Hit press 'h' or if you want to stay enter 's': ";
            cin>>izbor;

            if(izbor!='h' && izbor!='s')
                throw invalid_argument("Invalid choice!");

            if(izbor=='h'){
                int k=vleciKarta();
                string znak=sign();
                cout<<"You drew: "<<(k>=11?10:k)<<znak<<endl;

                player.dodadiKarta(k);
                cout<<"Your total now is: "<<player.getTotal()<<endl;

                if(player.getTotal()>21){
                    pobednik(player, dealer);
                    return;
                }
            }

        }while(izbor=='h');

        while(dealer.getTotal()<17){
            int r=vleciKarta();
            string s=sign();
            cout<<"Dealer draws: "<<(r>=11?10:r)<<s<<endl;
            dealer.dodadiKarta(r);
        }

        pobednik(player, dealer);
    }
};

int main() {
    srand(time(0));

    try {
        Blackjack game;

        while (true) {
            game.play();

            bool again = game.IgrajPak();

            if (!again) {
                cout << "\nThank you for playing our game!\n";
                cout << "Made by: Jovana Cvetkovska.\n";
                break;
            }
        }
    }
    catch (exception& e) {
        cout << "\nException caught: " << e.what() << endl;
    }

    return 0;
}
