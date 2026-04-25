#include <SDL_image.h>

#include <exception>

#include "Image.h"

struct Texture_deleter
{
  void operator()(SDL_Texture* t) const
  {
    SDL_DestroyTexture(t);
  }
};

Image::Image()
{

}

Image::Image(Moteur& moteur, const std::string& nomDuFichier, bool transparenceCouleur)
  : _moteur(&moteur)
{
  // Chargement de l'image dans une surface
  SDL_Surface* surface = IMG_Load(nomDuFichier.c_str());
  if (surface == nullptr)
    throw std::runtime_error("Impossible de charger " + nomDuFichier);

  // Si demandé, on rend le blanc (255, 255, 255) transparent
  if (transparenceCouleur)
  {
      // SDL_MapRGB crée le code couleur correspondant au blanc pour le format de l'image
      Uint32 blanc = SDL_MapRGB(surface->format, 255, 255, 255);
      // On définit cette couleur comme étant la couleur de transparence (Color Key)
      SDL_SetColorKey(surface, SDL_TRUE, blanc);
  }

  // Création de la texture à partir de la surface
  _texture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(_moteur->getRenderer(), surface),
                                          Texture_deleter());

  // On active le mode de mélange pour gérer la transparence (alpha)
  SDL_SetTextureBlendMode(_texture.get(), SDL_BLENDMODE_BLEND);

  // Initialisation du rectangle source (toute l'image par défaut)
  _rectangle.x = 0;
  _rectangle.y = 0;
  _rectangle.w = surface->w;
  _rectangle.h = surface->h;

  _hauteur = surface->h;
  _largeur = surface->w;

  // On libère la surface qui n'est plus nécessaire après la création de la texture
  SDL_FreeSurface(surface);
}

void Image::selectionnerRectangle(int x, int y, int largeur, int hauteur)
{
  _rectangle.x = x;
  _rectangle.y = y;
  _rectangle.w = largeur;
  _rectangle.h = hauteur;
}

void Image::dessiner(int x, int y) const
{
  SDL_Rect target;
  target.x = x * ECHELLE;
  target.y = y * ECHELLE;
  target.w = _rectangle.w * ECHELLE;
  target.h = _rectangle.h * ECHELLE;
  SDL_RenderCopy(_moteur->getRenderer(), _texture.get(), &_rectangle, &target);
}

int Image::getHauteur() const
{
  return _hauteur;
}

int Image::getLargeur() const
{
  return _largeur;
}
