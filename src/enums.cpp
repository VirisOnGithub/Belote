enum Couleur
{
    coeur = 0,
    carreau = 1,
    pique = 2,
    trefle = 3,
    rien = 4,
};

enum ChiffreCarte
{
    as = 0,
    dix = 1,
    roi = 2,
    dame = 3,
    valet = 4,
    neuf = 5,
    huit = 6,
    sept = 7,
};

enum ValeurCarteNonAtout
{
    asNonAtout = 11,
    dixNonAtout = 10,
    roiNonAtout = 4,
    dameNonAtout = 3,
    valetNonAtout = 2,
    neufNonAtout = 0,
    huitNonAtout = 0,
    septNonAtout = 0,
};

enum ValeurCarteAtout
{
    asAtout = 11,
    dixAtout = 10,
    roiAtout = 4,
    dameAtout = 3,
    valetAtout = 20,
    neufAtout = 14,
    huitAtout = 0,
    septAtout = 0,
};