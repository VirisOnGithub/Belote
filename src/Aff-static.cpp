#include "Affichage.h"
#include "imgui-master/imgui.h"

const char *AtouttoStr(Couleur c)
{
    switch (c)
    {
    case coeur:
        return "coeur";
    case carreau:
        return "carreau";
    case pique:
        return "pique";
    case trefle:
        return "trefle";
    case rien:
        return "rien";
    default:
        return "erreur";
    }
}

void Affichage::afficherMainRetourneeGraphiqueHaut1(int nbCartes)
{
    // Assurez-vous que la carte est définie
    sf::Texture texture;
    if (!texture.loadFromFile("../assets/back/BlueCardBack.png"))
    {
        std::cerr << "Erreur de chargement de la texture" << std::endl;
    }
    else
    {
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setScale(0.55, 0.55);
        int CardWidth = sprite.getGlobalBounds().width;
        int CardHeight = sprite.getGlobalBounds().height;
        for (int i = 0; i < nbCartes; i++)
        {
            sprite.setPosition((window.getSize().x - CardWidth * (nbCartes + 1) / 2.) / 2. + i * CardWidth / 2., -120);
            window.draw(sprite);
        }
    }
}

void Affichage::afficherMainRetourneeGraphiqueDroite1(int nbCartes)
{
    sf::Texture texture;
    if (!texture.loadFromFile("../assets/back/90DegBlueCardBack.png"))
    {
        std::cerr << "Erreur de chargement de la texture" << std::endl;
    }
    else
    {
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setScale(0.55, 0.55);
        int CardWidth = sprite.getGlobalBounds().width;
        int CardHeight = sprite.getGlobalBounds().height;
        for (int i = 0; i < nbCartes; i++)
        {
            sprite.setPosition(-120, (window.getSize().y - CardHeight * (nbCartes + 1) / 2.) / 2. + i * CardHeight / 2.);
            window.draw(sprite);
        }
        sprite.setScale(1, 1);
    }
}

void Affichage::afficherMainRetourneeGraphiqueGauche1(int nbCartes)
{
    sf::Texture texture;
    if (!texture.loadFromFile("../assets/back/90DegBlueCardBack.png"))
    {
        std::cerr << "Erreur de chargement de la texture" << std::endl;
    }
    else
    {
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setScale(0.55, 0.55);
        int CardWidth = sprite.getGlobalBounds().width;
        int CardHeight = sprite.getGlobalBounds().height;
        for (int i = 0; i < nbCartes; i++)
        {
            sprite.setPosition(window.getSize().x - 120, (window.getSize().y - CardHeight * (nbCartes + 1) / 2.) / 2. + i * CardHeight / 2.);
            window.draw(sprite);
        }
        sprite.setScale(1, 1);
    }
}

void Affichage::afficherMainGraphique(MainJoueur main)
{
    int nbCartesAffichees = main.getCartesG().size();
    cartesG.clear();
    auto cartes = main.getCartesG();

    for (int i = 0; i < nbCartesAffichees; i++)
    {
        sf::Sprite sprite;
        sprite.setTexture(*textures[cartes[i]]);
        sprite.setScale(0.9, 0.9);

        // Vérifiez que les textures sont chargées correctement
        if (textures[cartes[i]]->getSize().x == 0)
        {
            std::cout << "Erreur de chargement de la texture pour la carte : " << cartes[i].toAnsiString() << std::endl;
        }

        cartesG.push_back(sprite);
    }

    if (!cartesG.empty())
    {
        int CardWidth = textures[cartes[0]]->getSize().x * cartesG[0].getScale().x;  // Prendre en compte l'échelle de la carte
        int CardHeight = textures[cartes[0]]->getSize().y * cartesG[0].getScale().y; // Prendre en compte l'échelle de la carte
        float totalWidth = cartesG.size() * CardWidth;                               // La largeur totale des cartes

        for (int i = 0; i < cartesG.size(); i++)
        {
            cartesG[i].setPosition((window.getSize().x - totalWidth) / 2.0f + i * (CardWidth), window.getSize().y - CardHeight / 2.);
            window.draw(cartesG[i]);
        }
    }
    else
    {
        std::cerr << "Erreur : aucune carte à dessiner" << std::endl;
    }
}

sf::Font Affichage::loadFont()
{
    sf::Font font;
    if (!font.loadFromFile("../src/fonts/GravitasOne-Regular.ttf"))
    {
        std::cerr << "Error loading font" << std::endl;
    }
    else
    {
        std::cout << "Font loaded" << std::endl;
    }
    return font;
}

void Affichage::showAtoutPreneur()
{
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::Begin("Atout", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    ImVec2 pos = ImVec2(50, 10);
    ImGui::SetWindowPos(pos, ImGuiCond_Once);
    ImGui::SetWindowSize(ImVec2(250, 50), ImGuiCond_Always);
    ImGui::Text("Le preneur est le joueur %d", atoutPreneur + 1);
    ImGui::Text("L'atout est %s", AtouttoStr(atout));
    ImGui::End();
    ImGui::PopStyleColor(1);
    ImGui::PopStyleVar(1);
}

void Affichage::showError(std::string message)
{
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::Begin("Erreur", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    ImVec2 pos = ImVec2(window.getSize().x - 500, 0);
    ImGui::SetWindowPos(pos, ImGuiCond_Once);
    ImGui::SetWindowSize(ImVec2(500, 50), ImGuiCond_Always);
    ImGui::Text("%s", message.c_str());
    ImGui::End();
    ImGui::PopStyleColor(1);
    ImGui::PopStyleVar(1);
}

void Affichage::showTrumpTakerBadge(int indexJoueur)
{
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::Begin("AtoutBadge", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    ImVec2 pos;
    int res = (atoutPreneur-indexJoueur+4)%4;
    float trumpSize = texturesCouleurs[atout].getSize().x;
    std::cout << "res : " << res << std::endl;
    float CardHeight = 303/2., CardWidth = 208/2.;
    switch (res)
    {
        case 0:
            pos = ImVec2(window.getSize().x/2. - trumpSize/2, window.getSize().y - CardHeight - trumpSize);
            break;
        case 1:
            pos = ImVec2(CardWidth + trumpSize, window.getSize().y/2. - trumpSize/2);
            break;
        case 2:
            pos = ImVec2(window.getSize().x/2. -trumpSize/2, CardHeight + trumpSize);
            break;
        default:
            pos = ImVec2(window.getSize().x - CardWidth - trumpSize, window.getSize().y/2. - trumpSize/2);
            break;
    }
    ImGui::SetWindowPos(pos, ImGuiCond_Always);
    ImGui::SetWindowSize(ImVec2(trumpSize+2, trumpSize+2), ImGuiCond_Always);
    ImGui::Image((void *)(uintptr_t)texturesCouleurs[atout].getNativeHandle(), ImVec2(50, 50));
    ImGui::End();
    ImGui::PopStyleColor(1);
    ImGui::PopStyleVar(1);
}