//O firmă v-a cerut ajutorul pentru a crea un demo al unei aplicații de Blackjack.


#include <bits/stdc++.h>

using namespace std;

class LcgGenerator
{
private:
    uint16_t mA;
    uint16_t mC;
    uint16_t mCurrentX;
    uint16_t mM;
public:
    LcgGenerator(uint16_t a, uint16_t c, uint16_t x, uint16_t m) : mA(a), mC(c), mCurrentX(x), mM(m) {}
    uint16_t next()
    {
        mCurrentX = (mA * mCurrentX + mC) % mM;
        return mCurrentX;
    }
};

class Card
{
private:
    string mSuite;
    uint16_t mValue;
public:
    Card(const string& suite, uint16_t value) : mSuite(suite), mValue(value) {}
    bool operator == (const Card& c) const
    {
        if(mSuite == c.mSuite && mValue == c.mValue) return true;
        return false;
    }
    string toString() const
    {
        return to_string(mValue) + "," + mSuite;
    }
    string getSuite() const
    {
        return mSuite;
    }
    uint16_t getValue() const
    {
        return mValue;
    }
    void setSuite(string suite)
    {
        mSuite = suite;
    }
    void setValue(uint16_t value)
    {
        mValue = value;
    }
    bool isFake() const
    {
        if((mSuite != "rosu" && mSuite != "negru" && mSuite != "romb" && mSuite != "trefla") ||
        (mValue < 2 || mValue > 14)) return true;
        return false;
    }
    uint16_t getBlackjackValue() const
    {
        if(mValue >= 2 && mValue <= 11) return mValue;
        return 10;
    }
};

class CardPack
{
    vector<Card> mCards;
    uint16_t mCurrentIndex;
public:
    CardPack(bool empty = true) : mCurrentIndex(0)
    {
        if(empty == false)
        {
            for(int count = 0; count < 4; count++)
            for(int i = 2; i <= 14; i++)
            {
                if(i == 11) continue;
                if(count == 0) mCards.push_back(Card("rosu", i));
                if(count == 1) mCards.push_back(Card("negru", i));
                if(count == 2) mCards.push_back(Card("romb", i));
                if(count == 3) mCards.push_back(Card("trefla", i));
            }
        }
    }
    bool goodForBackjack() const
    {
        for(int i = 0; i < mCards.size(); i++)
        {
            if(mCards[i].isFake()) return false;
        }
        return true;
    }
    bool ok() const
    {
        if(mCards.size() != 52) return false;
        for(int i = 0; i < mCards.size() - 1; i++)
        for(int j = i + 1; j < mCards.size(); j++)
        {
            if(mCards[i] == mCards[j]) return false;
        }
        for(int i = 0; i < mCards.size(); i++)
        {
            if(mCards[i].isFake()) return false;
        }
        return true;
    }
    void addCard(const Card& c)
    {
        mCards.push_back(c);
    }
    void shuffle(uint16_t a1, uint16_t c1, uint16_t x01, uint16_t a2, uint16_t c2, uint16_t x02)
    {
        mCurrentIndex = 0;
        LcgGenerator L1(a1, c1, x01, mCards.size());
        LcgGenerator L2(a2, c2, x02, mCards.size());
        for(int i = 0; i < 50; i++)
        {
            swap(mCards[L1.next()], mCards[L2.next()]);
        }
    }
    void printPack() const
    {
        for(int i = 0; i < mCards.size(); i++)
        {
            cout << mCards[i].toString() << endl;
        }
    }
    Card nextCard()
    {
        mCurrentIndex++;
        return mCards[mCurrentIndex - 1];
    }
};

class Player
{
public:
    string mName = "Dealer";
    uint16_t mMoney = 0;
    uint16_t mPoints;
    Player(string name, uint16_t money) : mName(name), mMoney(money), mPoints(0) {}
    string toString() const
    {
        return mName + ": " + to_string(mMoney);
    }
    void pick(const Card& c)
    {
        mPoints += c.getBlackjackValue();
    }
    void play(CardPack& cp)
    {
        while(mPoints < 17)
        {
            this->pick(cp.nextCard());
        }
    }
    void newRound()
    {
        mPoints = 0;
    }
    bool lostRound() const
    {
        if(mPoints > 21) return true;
        return false;
    }
    uint16_t getPoints() const
    {
        return mPoints;
    }
    void operator--()
    {
        mMoney -= 10;
    }
    void operator++()
    {
        mMoney += 10;
    }
    bool lostGame() const
    {
        if(mMoney < 10) return true;
        return false;
    }
};

int main()
{
    string command;
    cin >> command;
    if(command == "check_cards")
    {
        uint8_t nrcarte;
        char stema[31];
        CardPack cp(true);
        while(scanf("%hhu,%s\n", &nrcarte, stema) != EOF)
        {
            string stem(stema);
            cp.addCard(Card(stem, nrcarte));
        }
        if(cp.ok())
        {
            printf("Pachet OK\n");
            return 0;
        }
        if(cp.goodForBackjack() == 0) printf("Pachet masluit\n");
        if(cp.goodForBackjack()) printf("Pregatit pentru Blackjack\n");
    }
    if(command == "shuffle_cards")
    {
        int a1, c1, x01, a2, c2, x02;
        cin >> a1 >> c1 >> x01 >> a2 >> c2 >> x02;
        uint8_t nrcarte;
        char stema[31];
        CardPack cp(true);
        while(scanf("%hhu,%s\n", &nrcarte, stema) != EOF)
        {
            string stem(stema);
            cp.addCard(Card(stem, nrcarte));
        }
        cp.shuffle(a1, c1, x01, a2, c2, x02);
        cp.printPack();
    }
    if(command == "play_game")
    {
        int a1, c1, x01, a2, c2, x02;
        int n;
        string nume;
        uint32_t bani;
        cin >> n;
        vector<Player> players;
        for(int i = 0; i < n; i++)
        {
            cin >> nume >> bani;
            players.push_back(Player(nume, bani));
        }
        players.push_back(Player("Dealer", 0));
        CardPack cp(false);
        while(cin >> a1 >> c1 >> x01 >> a2 >> c2 >> x02)
        {
            cp.shuffle(a1, c1, x01, a2, c2, x02);
            for(int i = 0; i < players.size(); i++)
            {
                players[i].pick(cp.nextCard());
                players[i].pick(cp.nextCard());
            }
            for(int i = 0; i < players.size() - 1; i++)
            {
                players[i].play(cp);
                if(players[i].lostRound()) --players[i];
            }
            players[players.size() - 1].play(cp);
            if(players[players.size() - 1].lostRound())
            {
                for(int i = 0; i < players.size() - 1; i++)
                {
                    if(players[i].lostRound() == 0) ++players[i];
                }
            }
            else for(int i = 0; i < players.size() - 1; i++)
            {
                if(players[i].lostRound() == 0 && players[i].getPoints() > players[players.size() - 1].getPoints())
                    ++players[i];
                if(players[i].lostRound() == 0 && players[i].getPoints() < players[players.size() - 1].getPoints())
                    --players[i];
            }
            for(int i = 0; i < players.size() - 1; i++)
            {
                if(players[i].lostGame())
                {
                    players.erase(players.begin() + i);
                    i--;
                }
            }
            for(int i = 0; i < players.size(); i++)
            {
                players[i].newRound();
            }
        }
        for(int i = 0; i < players.size() - 1; i++)
            {
                cout << players[i].toString() << endl;
            }
    }
    return 0;
}