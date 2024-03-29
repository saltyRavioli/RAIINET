#include <iostream>
#include "textdisplay.h"
#include "Cell.h"
#include "Player.h"
#include <sstream>
using namespace std;

TextDisplay::TextDisplay(int n): gridSize{n}, curPlayer{0} {
  for (int i=0; i<gridSize; i++) {
    theDisplay.emplace_back(vector<char>());
    for (int j=0; j<gridSize; j++) {
      theDisplay[i].emplace_back('.');
    }
  }

  for (int i=0; i<4; i++) {
    links.emplace_back(vector<string>());
    isLinkRevealed.emplace_back(vector<bool>());
    for (int j=0; j<8; j++) {
      links[i].emplace_back("");
      isLinkRevealed[i].emplace_back(false);
    }
    numLinksDownloaded.emplace_back(0);
    numVirusesDownloaded.emplace_back(0);
    numOfAbilities.emplace_back(5);
  }
}

TextDisplay::~TextDisplay() {}

void TextDisplay::changePlayer(int nextPlayer) {
  curPlayer = nextPlayer;
}

void TextDisplay::notify(Cell &c) {
  int x = c.getX();
  int y = c.getY();
  Link * link = c.getLink();
  if (link == nullptr || link->getIsDead()) {
    theDisplay[y][x] = c.getType();
  } else {
    theDisplay[y][x] = link->getId();
  }
}

void TextDisplay::notify(Player &p) {
  numLinksDownloaded[p.getId()] = p.getDownloadCount();
  numVirusesDownloaded[p.getId()] = p.getVirusCount();
  numOfAbilities[p.getId()] = p.getAbilityCount();
  int index = 0;
  for (auto l = p.getLinkBeginIterator(); l != p.getLinkEndIterator(); ++l) {
    stringstream ss;
    ss << *(*l);
    links[p.getId()][index] = ss.str();
    isLinkRevealed[p.getId()][index] = (*(*l)).getReveal();
    ++index;
  }
}
 
void TextDisplay::printPlayer(ostream &out, int playerID) const {
    // TO DO: make player have an observer so text display can do this
    out << "Player " << (playerID+1) << ":\n";
    out << "Downloaded: " << to_string(numLinksDownloaded[playerID]) << "D, " << to_string(numVirusesDownloaded[playerID]) << "V" << "\n";
    out << "Abilities: " << numOfAbilities[playerID] << "\n";
    for (int i=0; i<4; i++) {
      if (playerID == curPlayer || isLinkRevealed[playerID][i]) out << links[playerID][i] << ' ';
      else {
        string output = links[playerID][i].substr(0, 2)+" ? ";
        out << output << ' ';
      }
    }
    out << '\n';
    for (int i=4; i<8; i++) {
      if (playerID == curPlayer || isLinkRevealed[playerID][i]) out << links[playerID][i] << ' ';
      else {
        string output = links[playerID][i].substr(0, 2)+" ? ";
        out << output << ' ';
      }
    }
    out << '\n';
}

ostream& operator<<(ostream &out, const TextDisplay &td) {
  td.printPlayer(out, (td.curPlayer+1)%2); // TO DO: this doesn't work for 4 players
  out << "========" << '\n';
  for (int i=0; i<td.gridSize; i++) {
    for (int j=0; j<td.gridSize; j++) {
      int displayY = i; 
      int displayX = j;
      if (td.curPlayer == 0) displayY = td.gridSize-1 - i; 
      else if (td.curPlayer == 1) displayX = td.gridSize-1 - j;
      out << td.theDisplay[displayY][displayX];
    }
    out << '\n';
  }
  out << "========" << '\n';
  td.printPlayer(out, td.curPlayer);
  return out;
}

