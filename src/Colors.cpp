#include "Colors.h"

const Color dBlu = {72, 12, 168, 255};
const Color dGrn = {47, 230, 23, 255};
const Color dRed = {232, 18, 18, 255};
const Color dOrg = {226, 116, 17, 255};
const Color dYlw = {237, 234, 4, 255};
const Color dCya = {21, 204, 209, 255};
const Color dPur = {166, 0, 247, 255};
const Color dGry = {26, 31, 40, 155};
const Color rose = {247, 37, 133, 255};
const Color fDan = {181, 37, 133, 255};
const Color Grap = {114, 9, 183, 255};
const Color cBlu = {86, 11, 173, 255};
const Color Zafr = {58, 12, 163, 255};
const Color pBlu = {63, 55, 201, 255};
const Color nBlu = {67, 97, 238, 255};
const Color sBlu = {76, 201, 240, 255};

vector<Color> GetColors()
{
  vector<Color> colors = {dGry, dBlu, dGrn, dRed, dOrg, dYlw, dCya, dPur, rose, fDan, Grap, cBlu, Zafr, pBlu, nBlu, sBlu};
  return colors;
}