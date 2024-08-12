#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

bool isAlmostWhiteColor(int r, int g, int b) {
    return abs(r - 175) <= 10 && abs(g - 191) <= 10 && abs(b - 204) <= 10;
}

int main() {
    RenderWindow window(VideoMode(800, 800), "Coffee", Style::Default);
    Texture coffeeTexture;

    if (!coffeeTexture.loadFromFile("cup.jpg")) {
        // Handle error if texture fails to load
        return -1;
    }

    Sprite coffeeSprite;
    coffeeSprite.setTexture(coffeeTexture);

    float y = 513;
    float endY = 170;

    vector<RectangleShape> coffee;
    Image coffeeImage = coffeeTexture.copyToImage();
    Vector2u imageSize = coffeeImage.getSize();

    // Calculate the rectangles only once
    while (y > endY) {
        RectangleShape rect;
        bool foundColor = false;

        for (unsigned int xit = 0; xit < imageSize.x; xit++) {
            Color pixelColor = coffeeImage.getPixel(xit, static_cast<unsigned int>(y));
            if (isAlmostWhiteColor(static_cast<int>(pixelColor.r), static_cast<int>(pixelColor.g), static_cast<int>(pixelColor.b))) {
                if (!foundColor) {
                    rect.setPosition(Vector2f(static_cast<float>(xit), static_cast<float>(y)));
                    Color coffeeColor(111,78,55, 180);
                    rect.setFillColor(coffeeColor);
                    foundColor = true;
                }
                // Extend the rectangle width
                rect.setSize(Vector2f(static_cast<float>(xit - rect.getPosition().x + 1), 0.5f));
            }
        }

        if (foundColor) {
            coffee.push_back(rect);
        }

        y -= 0.5f;  // Decrement y to move upwards in the image
    }

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(coffeeSprite);

        for (const auto& rect : coffee) {
            window.draw(rect);
        }

        window.display();
    }

    return 0;
}
