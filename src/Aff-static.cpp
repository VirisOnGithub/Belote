#include "Affichage.h"
#include "imgui-master/imgui.h"
#include <SFML/Graphics/Texture.hpp>
#include <cassert>
#include <SFML/Audio/Music.hpp>

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

void Affichage::loadMusic()
{
    if (!music.openFromFile("../assets/mix.ogg"))
    {
        std::cerr << "Erreur de chargement de la musique" << std::endl;
    }
    music.setLoop(true);
    music.setVolume(0);
    music.play();
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
    assert(!main.main.empty());
    assert(main.main.size() <= 8 && main.main.size() > 0);
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
        float totalWidth = (cartesG.size() + 1) / 2. * CardWidth;                    // La largeur totale des cartes

        for (int i = 0; i < cartesG.size(); i++)
        {
            cartesG[i].setPosition((window.getSize().x - totalWidth) / 2.0f + i * (CardWidth / 2.0f), window.getSize().y - CardHeight / 2.);
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
    ImGui::TextWrapped("%s", message.c_str());
    ImGui::End();
    ImGui::PopStyleColor(1);
    ImGui::PopStyleVar(1);
}

void Affichage::showTrumpTakerBadge()
{
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::Begin("AtoutBadge", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    ImVec2 pos;
    int res = (atoutPreneur - indexJoueur + 4) % 4;
    float trumpSize = texturesCouleurs[atout].getSize().x;
    float CardHeight = 303 / 2., CardWidth = 208 / 2.;
    switch (res)
    {
    case 0:
        pos = ImVec2(window.getSize().x / 2. - trumpSize / 2, window.getSize().y - CardHeight - trumpSize);
        break;
    case 1:
        pos = ImVec2(CardWidth + trumpSize, window.getSize().y / 2. - trumpSize / 2);
        break;
    case 2:
        pos = ImVec2(window.getSize().x / 2. - trumpSize / 2, CardHeight + trumpSize);
        break;
    default:
        pos = ImVec2(window.getSize().x - CardWidth - trumpSize, window.getSize().y / 2. - trumpSize / 2);
        break;
    }
    ImGui::SetWindowPos(pos, ImGuiCond_Always);
    ImGui::SetWindowSize(ImVec2(trumpSize + 2, trumpSize + 2), ImGuiCond_Always);
    ImGui::Image((void *)(uintptr_t)texturesCouleurs[atout].getNativeHandle(), ImVec2(50, 50));
    ImGui::End();
    ImGui::PopStyleColor(1);
    ImGui::PopStyleVar(1);
}

void Affichage::showParameters()
{
    sf::Texture &texture = settings ? crossTexture : settingsTexture;
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::Begin("Parametres", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    ImVec2 pos = ImVec2(window.getSize().x - 100, 50);
    ImGui::SetWindowPos(pos, ImGuiCond_Once);
    ImGui::SetWindowSize(ImVec2(75, 75), ImGuiCond_Always);
    if (ImGui::ImageButton((void *)(uintptr_t)texture.getNativeHandle(), ImVec2(50, 50)))
    {
        settings = !settings;
    }
    ImGui::End();
    ImGui::PopStyleColor(1);
    ImGui::PopStyleVar(1);
}

void Affichage::showScores()
{
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::Begin("Scores", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    ImVec2 pos = ImVec2(150, window.getSize().y - 50);
    ImGui::SetWindowPos(pos, ImGuiCond_Once);
    ImGui::SetWindowSize(ImVec2(250, 50), ImGuiCond_Always);
    ImGui::Text("Score equipe 1 : %d", table.Equipe1.getScore());
    ImGui::Text("Score equipe 2 : %d", table.Equipe2.getScore());
    ImGui::End();
    ImGui::PopStyleColor(1);
    ImGui::PopStyleVar(1);
}

void Affichage::showJoueur()
{
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::Begin("Joueur", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    ImVec2 pos = ImVec2(50, window.getSize().y - 50);
    ImGui::SetWindowPos(pos, ImGuiCond_Once);
    ImGui::SetWindowSize(ImVec2(250, 50), ImGuiCond_Always);
    ImGui::Text("Joueur %d", indexJoueur + 1);
    ImGui::End();
    ImGui::PopStyleColor(1);
    ImGui::PopStyleVar(1);
}