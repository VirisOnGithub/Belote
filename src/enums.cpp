/**
 * @brief Enumeration for the different colors in a card deck.
 */
enum Couleur
{
    coeur = 0,   /**< Heart */
    carreau = 1, /**< Diamond */
    pique = 2,   /**< Spade */
    trefle = 3,  /**< Club */
    rien = 4     /**< None */
};

/**
 * @brief Enumeration for the different ranks of a card.
 */
enum ChiffreCarte
{
    as = 0,    /**< Ace */
    dix = 1,   /**< Ten */
    roi = 2,   /**< King */
    dame = 3,  /**< Queen */
    valet = 4, /**< Jack */
    neuf = 5,  /**< Nine */
    huit = 6,  /**< Eight */
    sept = 7   /**< Seven */
};

/**
 * @brief Enumeration for the values of a card when it is not a trump card.
 */
enum ValeurCarteNonAtout
{
    asNonAtout = 11,   /**< Ace */
    dixNonAtout = 10,  /**< Ten */
    roiNonAtout = 4,   /**< King */
    dameNonAtout = 3,  /**< Queen */
    valetNonAtout = 2, /**< Jack */
    neufNonAtout = 0,  /**< Nine */
    huitNonAtout = 0,  /**< Eight */
    septNonAtout = 0   /**< Seven */
};

/**
 * @brief Enumeration for the values of a card when it is a trump card.
 */
enum ValeurCarteAtout
{
    asAtout = 11,    /**< Ace */
    dixAtout = 10,   /**< Ten */
    roiAtout = 4,    /**< King */
    dameAtout = 3,   /**< Queen */
    valetAtout = 20, /**< Jack */
    neufAtout = 14,  /**< Nine */
    huitAtout = 0,   /**< Eight */
    septAtout = 0    /**< Seven */
};
