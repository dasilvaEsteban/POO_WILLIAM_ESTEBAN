// POO_WILLIAM_ESTEBAN : définit le point d'entrée de l'application.
// Inclusion des bibliothèques nécessaires
#include "traffic_light.hpp"
#include "feuxTricolor.hpp"
#include "car.hpp"
#include "pieton.hpp"
#include "bus.hpp"
#include <cstdlib>
#include <iostream> 
#include <thread>   
#include <mutex>
#include <vector>
#include <random>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std::chrono_literals;
using namespace std;
using namespace sf;

//Chemin d'acces aux images
#define _PATH_IMG_ "../../../../SFML/SFML/img/"
const std::string path_image(_PATH_IMG_);

//Déclaration de la couleur orange pour SFML
static const sf::Color Orange(255, 165, 0);

// Déclaration des durées d'attente pour les transitions de feux
const auto time_transit = 3s;
const auto time_wait = 8s;

// Mutex et variables conditionnelles pour la gestion des feux de circulation
std::mutex traffic_mutex;
std::condition_variable traffic_cv;
Traffic_color current_master_traffic_light = Traffic_color::red;
Traffic_color current_slave_traffic_light = Traffic_color::red;

// Déclaration des conteneurs pour les voitures, piétons et bus
vector<Car> cars;
mutex car_mutex;
vector<Pieton> pietons;
vector<Bus> buses;

// Fonction pour convertir un état de feu en couleur SFML
const sf::Color& get_SFML_color(const Traffic_light& traffic_light)
{
    switch (traffic_light.get_traffic_color())
    {
    case Traffic_color::green:
        return sf::Color::Green;
    case Traffic_color::red:
        return sf::Color::Red;
    }
    return Orange;
}


// Fonction qui contrôle l'alternance des feux tricolores principaux (master) et secondaires (slave)
void run_traffic_light(Traffic_light& traffic_light_master, Traffic_light& traffic_light_slave, std::stop_token stop_token)
{
    traffic_light_master.set_traffic_color(Traffic_color::green);
    traffic_light_slave.set_traffic_color(Traffic_color::red);
    while (!stop_token.stop_requested())
    {
        {
            std::lock_guard<std::mutex> lock(traffic_mutex);
            current_master_traffic_light = traffic_light_master.get_traffic_color();
            current_slave_traffic_light = traffic_light_slave.get_traffic_color();
        }
        traffic_cv.notify_all();

        std::this_thread::sleep_for(time_wait);
        if (traffic_light_master.get_traffic_color() == Traffic_color::green)
        {
            ++traffic_light_master;
            if (traffic_light_master.get_traffic_color() == Traffic_color::orange) {
                {
                    std::lock_guard<std::mutex> lock(traffic_mutex);
                    current_master_traffic_light = traffic_light_master.get_traffic_color();
                }
                traffic_cv.notify_all();

                std::this_thread::sleep_for(time_transit);
                ++traffic_light_master;
            }
            ++traffic_light_slave;
        }
        else
        {
            ++traffic_light_slave;
            if (traffic_light_slave.get_traffic_color() == Traffic_color::orange) {
                {
                    std::lock_guard<std::mutex> lock(traffic_mutex);
                    current_slave_traffic_light = traffic_light_slave.get_traffic_color();
                }
                traffic_cv.notify_all();
                std::this_thread::sleep_for(time_transit);
                ++traffic_light_slave;
            }
            ++traffic_light_master;
        }

    }
}

//Fonction qui affiche les états actuels des feux principaux (master) et secondaires (slave) dans la console
void print_traffic_light(Traffic_light& traffic_light_master, Traffic_light& traffic_light_slave, std::stop_token stop_token)
{
    while (!stop_token.stop_requested())
    {
        std::this_thread::sleep_for(1s);
        std::cout << "Taffic light master : " << traffic_light_master << " Taffic light slave : " << traffic_light_slave << std::endl;
    }
}

void spawn_cars(vector<Car>& cars, stop_token stop_token) {
    const int max_cars = 5; // Nombre maximum de voitures pouvant être créées
    const int max_par_coin = 2; // Nombre maximum de voitures par bord

    while (!stop_token.stop_requested()) {
        std::this_thread::sleep_for(3s); // Attendre 3 secondes avant chaque itération

        unique_lock<std::mutex> lock(car_mutex); // Synchronisation pour accéder à la liste des voitures
        if (cars.size() != max_cars) {
            std::default_random_engine generator(std::random_device{}());
            std::uniform_int_distribution<int> edge_dist(0, 3); // Génération aléatoire du bord d'apparition
            std::uniform_int_distribution<int> pattern_dist(1, 3); // Génération aléatoire du pattern
            int edge = edge_dist(generator);
            int pattern = pattern_dist(generator);

            // Comptabiliser le nombre de voitures par bord
            int nb_car_haut = 0;
            int nb_car_bas = 0;
            int nb_car_droite = 0;
            int nb_car_gauche = 0;

            for (auto& car : cars) {
                if (car.getY() > 620 && car.getAngle() == 270) nb_car_bas++;
                if (car.getY() < 180 && car.getAngle() == 90) nb_car_haut++;
                if (car.getX() > 620 && car.getAngle() == 180) nb_car_droite++;
                if (car.getX() < 180 && car.getAngle() == 0) nb_car_gauche++;
            }

            // Ajouter une voiture en fonction du bord d'apparition
            switch (edge) {
            case 0:
                if (nb_car_haut < max_par_coin) cars.push_back(Car(370, 0, 90, 0, pattern));
                break;
            case 1:
                if (nb_car_bas < max_par_coin) cars.push_back(Car(430, 765, 270, 0, pattern));
                break;
            case 2:
                if (nb_car_gauche < max_par_coin) cars.push_back(Car(0, 430, 0, 0, pattern));
                break;
            case 3:
                if (nb_car_droite < max_par_coin) cars.push_back(Car(765, 365, 180, 0, pattern));
                break;
            }
        }
    }
}
void spawn_pietons(vector<Pieton>& pietons, stop_token stop_token) {
    const int max_pietons = 8; // Nombre maximum de piétons pouvant être créés
    const int max_par_coin = 3; // Nombre maximum de piétons par bord

    while (!stop_token.stop_requested()) {
        std::this_thread::sleep_for(4s); // Attendre 4 secondes avant chaque itération

        if (pietons.size() != max_pietons) {
            std::default_random_engine generator(std::random_device{}());
            std::uniform_int_distribution<int> edge_dist(0, 3); // Génération aléatoire du bord d'apparition
            int edge = edge_dist(generator);

            // Comptabiliser le nombre de piétons par bord
            int nb_pieton_haut = 0;
            int nb_pieton_bas = 0;
            int nb_pieton_droite = 0;
            int nb_pieton_gauche = 0;

            for (auto& pieton : pietons) {
                if (pieton.getY() > 580 && pieton.getAngle() == 270) nb_pieton_bas++;
                if (pieton.getY() < 210 && pieton.getAngle() == 90) nb_pieton_haut++;
                if (pieton.getX() > 580 && pieton.getAngle() == 180) nb_pieton_droite++;
                if (pieton.getX() < 210 && pieton.getAngle() == 0) nb_pieton_gauche++;
            }

            // Ajouter un piéton en fonction du bord d'apparition
            switch (edge) {
            case 0:
                if (nb_pieton_haut < max_par_coin) pietons.push_back(Pieton(230, 0, 90, 0));
                break;
            case 1:
                if (nb_pieton_bas < max_par_coin) pietons.push_back(Pieton(580, 765, 270, 0));
                break;
            case 2:
                if (nb_pieton_gauche < max_par_coin) pietons.push_back(Pieton(0, 210, 0, 0));
                break;
            case 3:
                if (nb_pieton_droite < max_par_coin) pietons.push_back(Pieton(765, 560, 180, 0));
                break;
            }
        }
    }
}
void spawn_buses(vector<Bus>& buses, stop_token stop_token) {
    const int max_buses = 4; // Nombre maximum de bus pouvant être créés
    const int max_par_coin = 2; // Nombre maximum de bus par bord

    while (!stop_token.stop_requested()) {
        std::this_thread::sleep_for(7s); // Attendre 7 secondes avant chaque itération

        if (buses.size() != max_buses) {
            std::default_random_engine generator(std::random_device{}());
            std::uniform_int_distribution<int> edge_dist(0, 3); // Génération aléatoire du bord d'apparition
            std::uniform_int_distribution<int> pattern_dist(1, 3); // Génération aléatoire du pattern
            int edge = edge_dist(generator);
            int pattern = pattern_dist(generator);

            // Comptabiliser le nombre de bus par bord
            int nb_bus_haut = 0;
            int nb_bus_bas = 0;
            int nb_bus_droite = 0;
            int nb_bus_gauche = 0;

            for (auto& bus : buses) {
                if (bus.getY() > 620 && bus.getAngle() == 270) nb_bus_bas++;
                if (bus.getY() < 180 && bus.getAngle() == 90) nb_bus_haut++;
                if (bus.getX() > 620 && bus.getAngle() == 180) nb_bus_droite++;
                if (bus.getX() < 180 && bus.getAngle() == 0) nb_bus_gauche++;
            }

            // Ajouter un bus en fonction du bord d'apparition
            switch (edge) {
            case 0:
                if (nb_bus_haut < max_par_coin) buses.push_back(Bus(300, 0, 90, 0, pattern));
                break;
            case 1:
                if (nb_bus_bas < max_par_coin) buses.push_back(Bus(500, 765, 270, 0, pattern));
                break;
            case 2:
                if (nb_bus_gauche < max_par_coin) buses.push_back(Bus(0, 500, 0, 0, pattern));
                break;
            case 3:
                if (nb_bus_droite < max_par_coin) buses.push_back(Bus(765, 305, 180, 0, pattern));
                break;
            }
        }
    }
}

//Fonction pour gérer le comportement des voitures, pietons et bus
void run_cars(vector<Car>& cars, vector<Pieton>& pietons, vector<Bus>& buses, stop_token stop_token) {
    const float safety_distance = 120.0f; // Distance de sécurité

    while (!stop_token.stop_requested()) {
        std::this_thread::sleep_for(10ms);

        unique_lock<std::mutex> lock(car_mutex); // Verrouiller pour travailler sur les voitures
        int indice = 0;

        for (auto& car : cars) {
            bool is_blocked = false;
            bool should_slow_down = false;

            {
                // Synchronisation avec les feux (indépendant pour chaque voiture)
                std::unique_lock<std::mutex> traffic_lock(traffic_mutex);

                // Vérification des feux pour bloquer seulement les voitures concernées
                if ((car.getY() > 640 && car.getY() < 670 && car.getAngle() == 270 && current_slave_traffic_light != Traffic_color::green) || // Bas vers Haut
                    (car.getY() < 160 && car.getY() > 130 && car.getAngle() == 90 && current_slave_traffic_light != Traffic_color::green) ||  // Haut vers Bas
                    (car.getX() > 640 && car.getX() < 670 && car.getAngle() == 180 && current_master_traffic_light != Traffic_color::green) || // Droite vers Gauche
                    (car.getX() < 160 && car.getX() > 130 && car.getAngle() == 0 && current_master_traffic_light != Traffic_color::green)) {    // Gauche vers Droite
                    is_blocked = true; // Bloquer cette voiture si les conditions sont remplies
                }
            }

            if (is_blocked) {
                indice++;
                continue; // Skip le reste du traitement pour cette voiture
            }

            // Vérification de la distance avec les autres voitures
            for (const auto& other_car : cars) {
                if (&car != &other_car) { // Ne pas se comparer à soi-même
                    float distance = car.distanceTo(other_car);
                    // Vérifier si une voiture est devant dans la même direction
                    if (distance < safety_distance && distance != numeric_limits<float>::infinity()) {
                        should_slow_down = true;
                        break;
                    }

                }
            }



            // Vérification de la distance avec les pietons
            for (const auto& pieton : pietons) {
                float distance = car.distanceToPiet(pieton);
                // Vérifier si une voiture est devant dans la même direction
                if (distance < safety_distance && distance != numeric_limits<float>::infinity()) {
                    should_slow_down = true;
                    break;
                }
            }



            // Vérification de la distance avec les bus
            for (const auto& bus : buses) {
                float distance = car.distanceToBus(bus);
                // Vérifier si un bus est devant dans la même direction
                if (distance < safety_distance && distance != numeric_limits<float>::infinity()) {
                    should_slow_down = true;
                    break;
                }
            }


            if (should_slow_down) {
                car.speedDown(); // Ralentir
            }
            else {
                car.speedUp(); // Réaccélérer
            }

            // Déplacer la voiture
            car.move();
            // Gérer les modèles de trajectoires
            if (car.getPatern() == 2) {
                if (
                    (190 <= car.getX() && car.getX() <= 600 && 190 <= car.getY() && car.getY() <= 600 && car.getAngle() != (car.getinitAngle() + 90))) {
                    car.turnRight();
                    if (car.getSpeed() > 1.5f) {
                        car.speedDown();
                        car.speedDown();
                    }
                }

            }
            else if (car.getPatern() == 3) {
                if (
                    (260 <= car.getX() && car.getX() <= 540 && 250 <= car.getY() && car.getY() <= 540 && car.getAngle() != (car.getinitAngle() - 90))) {
                    car.turnLeft();
                    if (car.getSpeed() > 1.5f) {
                        car.speedDown();
                        car.speedDown();
                    }
                }

            }

            // Supprimer les voitures hors écran
            if (car.getX() > 800 || car.getY() > 800 || car.getX() < 0 || car.getY() < 0) {
                cars.erase(cars.begin() + indice);
                indice--;
            }
            indice++;
        }
    }
}
void run_pietons(vector<Pieton>& pietons, vector<Car>& cars, vector<Bus>& buses, stop_token stop_token) {
    const float safety_distance = 70.0f; // Distance de sécurité

    while (!stop_token.stop_requested()) {
        std::this_thread::sleep_for(10ms);

        int indice = 0;
        for (auto& pieton : pietons) {
            bool is_blocked = false;
            bool should_slow_down = false;

            {
                // Synchronisation avec les feux (indépendant pour chaque pieton)
                std::unique_lock<std::mutex> traffic_lock(traffic_mutex);

                // Vérification des feux pour bloquer seulement les voitures concernées
                if ((pieton.getY() > 580 && pieton.getY() < 620 && pieton.getAngle() == 270 && current_slave_traffic_light != Traffic_color::green) || // Bas vers Haut
                    (pieton.getY() < 210 && pieton.getY() > 180 && pieton.getAngle() == 90 && current_slave_traffic_light != Traffic_color::green) ||  // Haut vers Bas
                    (pieton.getX() > 580 && pieton.getX() < 620 && pieton.getAngle() == 180 && current_master_traffic_light != Traffic_color::green) || // Droite vers Gauche
                    (pieton.getX() < 210 && pieton.getX() > 180 && pieton.getAngle() == 0 && current_master_traffic_light != Traffic_color::green)) {    // Gauche vers Droite
                    is_blocked = true; // Bloquer ce pieton si les conditions sont remplies
                }
            }

            if (is_blocked) {
                indice++;
                continue; // Skip le reste du traitement pour cette voiture
            }

            // Vérification de la distance avec les autres pietons
            for (const auto& other_pieton : pietons) {
                if (&pieton != &other_pieton) { // Ne pas se comparer à soi-même
                    float distance = pieton.distanceTo(other_pieton);
                    // Vérifier si un pieton est devant dans la même direction
                    if (distance < safety_distance) {
                        should_slow_down = true;
                        break;
                    }

                }
            }


            // Vérification de la distance avec les autres voitures
            for (const auto& other_car : cars) {
                float distance = pieton.distanceToCar(other_car);
                // Vérifier si une voiture est devant dans la même direction
                if (distance < safety_distance + 50) {
                    should_slow_down = true;
                    break;
                }
            }


            // Vérification de la distance avec les autres bus
            for (const auto& other_bus : buses) {
                float distance = pieton.distanceToBus(other_bus);
                // Vérifier si un bus est devant dans la même direction
                if (distance < safety_distance + 50) {
                    should_slow_down = true;
                    break;
                }
            }


            if (should_slow_down) {
                pieton.speedDown(); // Ralentir
            }
            else {
                pieton.speedUp(); // Réaccélérer
            }

            // Déplacer le pieton
            pieton.move();


            // Supprimer les pietons hors écran
            if (pieton.getX() > 800 || pieton.getY() > 800 || pieton.getX() < 0 || pieton.getY() < 0) {
                pietons.erase(pietons.begin() + indice);
                indice--;
            }
            indice++;
        }
    }
}
void run_buses(vector<Bus>& buses, vector<Pieton>& pietons, vector<Car>& cars, stop_token stop_token) {
    const float safety_distance = 120.0f; // Distance de sécurité

    while (!stop_token.stop_requested()) {
        std::this_thread::sleep_for(10ms);

        int indice = 0;

        for (auto& bus : buses) {
            bool is_blocked = false;
            bool should_slow_down = false;

            {
                // Synchronisation avec les feux (indépendant pour chaque bus)
                std::unique_lock<std::mutex> traffic_lock(traffic_mutex);

                // Vérification des feux pour bloquer seulement les bus concernées
                if ((bus.getY() > 640 && bus.getY() < 670 && bus.getAngle() == 270 && current_slave_traffic_light != Traffic_color::green) || // Bas vers Haut
                    (bus.getY() < 160 && bus.getY() > 130 && bus.getAngle() == 90 && current_slave_traffic_light != Traffic_color::green) ||  // Haut vers Bas
                    (bus.getX() > 640 && bus.getX() < 670 && bus.getAngle() == 180 && current_master_traffic_light != Traffic_color::green) || // Droite vers Gauche
                    (bus.getX() < 160 && bus.getX() > 130 && bus.getAngle() == 0 && current_master_traffic_light != Traffic_color::green)) {    // Gauche vers Droite
                    is_blocked = true; // Bloquer ce bus si les conditions sont remplies
                }
            }

            if (is_blocked) {
                indice++;
                continue; // Skip le reste du traitement pour ce bus
            }

            // Vérification de la distance avec les autres bus
            for (const auto& other_bus : buses) {
                if (&bus != &other_bus) { // Ne pas se comparer à soi-même
                    float distance = bus.distanceTo(other_bus);
                    // Vérifier si un bus est devant dans la même direction
                    if (distance < safety_distance && distance != numeric_limits<float>::infinity()) {
                        should_slow_down = true;
                        break;
                    }

                }
            }

            // Vérification de la distance avec les pietons
            for (const auto& pieton : pietons) {
                float distance = bus.distanceToPiet(pieton);
                // Vérifier si un pieton est devant dans la même direction
                if (distance < safety_distance && distance != numeric_limits<float>::infinity()) {
                    should_slow_down = true;
                    break;
                }
            }

            // Vérification de la distance avec les voitures
            for (const auto& car : cars) {
                float distance = bus.distanceToCar(car);
                // Vérifier si une voiture est devant dans la même direction
                if (car.getPatern() == 3 && bus.getPatern() == 3 && bus.getX() > 170 && bus.getX() < 630 && bus.getY() > 170 && bus.getY() < 630
                    && car.getX() > 170 && car.getX() < 630 && car.getY() > 170 && car.getY() < 630
                    && bus.getinitAngle() - 30 < bus.getAngle()) {
                    should_slow_down = true;
                    break;
                }
                if (distance < safety_distance && distance != numeric_limits<float>::infinity()) {
                    should_slow_down = true;
                    break;
                }
            }

            if (should_slow_down) {
                bus.speedDown(); // Ralentir
            }
            else {
                bus.speedUp(); // Réaccélérer
            }

            // Déplacer le bus
            bus.move();
            // Gérer les modèles de trajectoires
            if (bus.getPatern() == 2) {
                if (
                    (190 <= bus.getX() && bus.getX() <= 600 && 190 <= bus.getY() && bus.getY() <= 600 && bus.getAngle() != (bus.getinitAngle() + 90))) {
                    bus.turnRight();
                    if (bus.getSpeed() > 1.3f) {
                        bus.speedDown();
                        bus.speedDown();
                    }
                }

            }
            else if (bus.getPatern() == 3) {
                if (
                    (260 <= bus.getX() && bus.getX() <= 540 && 250 <= bus.getY() && bus.getY() <= 540 && bus.getAngle() != (bus.getinitAngle() - 90))) {
                    bus.turnLeft();
                    if (bus.getSpeed() > 1.3f) {
                        bus.speedDown();
                        bus.speedDown();
                    }
                }

            }

            // Supprimer les bus hors écran
            if (bus.getX() > 800 || bus.getY() > 800 || bus.getX() < 0 || bus.getY() < 0) {
                buses.erase(buses.begin() + indice);
                indice--;
            }
            indice++;
        }
    }
}


int main()
{
    // Chargement des textures des voitures, piétons, bus et fond
    Texture voitImg, pietonImg, busImg, backgroundImg;
    Sprite voitSprite, pietonSprite, busSprite, backgroundSprite;

    //Chargements des Images
    if (!voitImg.loadFromFile(path_image + "Voiture.png")) {
        cerr << "Erreur pendant le chargement des images" << endl;
        return EXIT_FAILURE; // On ferme le programme
    }
    if (!pietonImg.loadFromFile(path_image + "pieton.png")) {
        cerr << "Erreur pendant le chargement des images" << endl;
        return EXIT_FAILURE; // On ferme le programme
    }
    if (!busImg.loadFromFile(path_image + "Bus.png")) {
        cerr << "Erreur pendant le chargement des images" << endl;
        return EXIT_FAILURE; // On ferme le programme
    }
    if (!backgroundImg.loadFromFile(path_image + "carrefour.png")) {
        cerr << "Erreur pendant le chargement des images" << endl;
        return EXIT_FAILURE; // On ferme le programme
    }


    // Configuration des sprites

    voitSprite.setTexture(voitImg);
    sf::Vector2u carSize = voitImg.getSize(); // Taille de l'image de la voiture
    voitSprite.setOrigin(carSize.x / 2.0f, carSize.y / 2.0f); // Centre de l'image
    voitSprite.setScale(sf::Vector2f(1, 1));

    pietonSprite.setTexture(pietonImg);
    sf::Vector2u pietonhSize = pietonImg.getSize(); // Taille de l'image du pieton
    pietonSprite.setOrigin(pietonhSize.x / 2.0f, pietonhSize.y / 2.0f); // Centre de l'image
    pietonSprite.setScale(sf::Vector2f(0.3, 0.3));

    busSprite.setTexture(busImg);
    sf::Vector2u busSize = busImg.getSize(); // Taille de l'image du bus
    busSprite.setOrigin(busSize.x / 2.0f, busSize.y / 2.0f); // Centre de l'image
    busSprite.setScale(sf::Vector2f(0.3, 0.3));

    backgroundSprite.setTexture(backgroundImg);
    // Calculer le facteur d'échelle pour s'adapter à une fenêtre 800x800
    float scaleX = 800.f / backgroundImg.getSize().x;
    float scaleY = 800.f / backgroundImg.getSize().y;

    // Appliquer l'échelle au sprite
    backgroundSprite.setScale(scaleX, scaleY);

    sf::RenderWindow window(sf::VideoMode(800, 800), "My window");

    // Positionnement des Feux tricolores
    TrafficLightDrawable masterLight(612.5, 268, false);
    TrafficLightDrawable slaveLight(440, 613, true);
    TrafficLightDrawable masterLight2(158, 441, false);
    TrafficLightDrawable slaveLight2(268, 158, true);


    // Création d'une source de demande d'arrêt pour contrôler l'exécution des threads
    std::stop_source stopping;

    //Initialisation des feux de circulation avec la couleur rouge par défaut
    Traffic_light traffic_light_master{ Traffic_color::red };
    Traffic_light traffic_light_slave{ Traffic_color::red };

    //Lancements des threads
    jthread thread_traffic_light_master(run_traffic_light,std::ref(traffic_light_master), std::ref(traffic_light_slave), stopping.get_token());
    jthread write_traffic_light(print_traffic_light,std::ref(traffic_light_master), std::ref(traffic_light_slave), stopping.get_token());
    jthread spawn_bus(spawn_buses, ref(buses), stopping.get_token());
    jthread spawn_pieton(spawn_pietons, ref(pietons), stopping.get_token());
    jthread spawn_car(spawn_cars, ref(cars), stopping.get_token());
    jthread voiture(run_cars, ref(cars), ref(pietons), ref(buses), stopping.get_token());
    jthread pieton(run_pietons, ref(cars), ref(pietons), ref(buses), stopping.get_token());
    jthread bus(run_buses, ref(cars), ref(pietons), ref(buses), stopping.get_token());

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                stopping.request_stop();
                window.close();
                return 0;
            }
        }


        window.clear(sf::Color::Black);

        window.draw(backgroundSprite);

        for (const auto& car : cars)
        {

            voitSprite.setPosition(car.getX(), car.getY());
            voitSprite.setRotation(car.getAngle());
            window.draw(voitSprite);
        }

        for (const auto& pieton : pietons)
        {
            // Mettre à jour la position du sprite en fonction des coordonnées du piéton
            pietonSprite.setPosition(pieton.getX(), pieton.getY());

            // Mettre à jour la rotation du sprite en fonction de l'angle du piéton
            pietonSprite.setRotation(pieton.getAngle() + 90.0f);

            // Dessiner le sprite dans la fenêtre
            window.draw(pietonSprite);
        }


        for (const auto& bus : buses)
        {

            busSprite.setPosition(bus.getX(), bus.getY());
            busSprite.setRotation(bus.getAngle());
            window.draw(busSprite);
        }


        masterLight.setColor(traffic_light_master.get_traffic_color());
        slaveLight.setColor(traffic_light_slave.get_traffic_color());
        masterLight2.setColor(traffic_light_master.get_traffic_color());
        slaveLight2.setColor(traffic_light_slave.get_traffic_color());

        masterLight.draw(window);
        slaveLight.draw(window);
        masterLight2.draw(window);
        slaveLight2.draw(window);

        window.display();
    }

    return 0;
}
