BYGGINSTRUKTIONER

Detta projekt är skrivet i C++ och använder följande bibliotek:

SDL3

SDL3_image

SDL3_ttf

Programmet har utvecklats och testats i Visual Studio Code med MinGW.

Följande bibliotek måste vara installerade på systemet innan projektet kan byggas:

SDL3

SDL3_image

SDL3_ttf

Exempel på kompileringskommando (MinGW):

g++ main.cpp `
  src/engine/GameEngine.cpp src/engine/Renderer.cpp `
  src/game/Player.cpp src/game/Enemy.cpp src/game/Bullet.cpp src/game/EnemySpawner.cpp `
  -Iinclude -Iinclude/engine -Iinclude/game `
  -IC:/SDL2/SDL3-3.2.16/x86_64-w64-mingw32/include `
  -IC:/SDL2/SDL3_image-devel-3.2.2-mingw/SDL3_image-3.2.2/x86_64-w64-mingw32/include `
  -LC:/SDL2/SDL3-3.2.16/x86_64-w64-mingw32/lib `
  -LC:/SDL2/SDL3_image-devel-3.2.2-mingw/SDL3_image-3.2.2/x86_64-w64-mingw32/lib `
  -lSDL3 -lSDL3_image `
  -o build/debug/game.exe

Efter kompilering kan programmet startas med:

./build/debug/game.exe  

PROJEKTSTRUKTUR

Projektet är uppdelat i två huvuddelar:

Spelmotorn (den generella delen)

Spelimplementationen (den specifika delen)

Spelmotorns filer finns i:

src/engine/
include/engine/

Dessa filer innehåller generell funktionalitet såsom:

Spelloop (game loop)

Sprite-system

Rendering av grafik

Hantering av input

Kollisionsdetektering

Hantering av objekt som skapas och tas bort

Spelfiler finns i:

src/game/
include/game/

Dessa filer implementerar själva spelet genom att använda spelmotorns API.

RESURSER

Spelet använder resursfiler som finns i katalogen:

resources/

Den innehåller följande mappar:

resources/images/
resources/fonts/

Bilder som används i spelet:

Player.png

Enemy.png

Bullet.png

Typsnitt:

PressStart2P-Regular.ttf

HUR MAN STARTAR SPELET

Efter att programmet har kompilerats startas spelet genom att köra:

./game

Ett spel-fönster öppnas och spelet startar.

SPELBESKRIVNING

Spelet är ett enkelt tvådimensionellt top-down shooter-spel.

Spelvärlden innehåller flera typer av objekt (sprites):

Player

Enemy

Bullet

Spelaren styr en figur som kan röra sig över skärmen och skjuta projektiler mot fiender.

KONTROLLER

W – flytta uppåt
A – flytta åt vänster
S – flytta nedåt
D – flytta åt höger

SPACE – skjut projektil

Spelaren styrs med tangentbordet.

SPELMEKANIK

Fiender spawnar högst upp på skärmen och rör sig nedåt.

Spelarens uppgift är att skjuta fienderna innan de når botten av skärmen.

När en projektil kolliderar med en fiende:

Fienden tas bort

Projektilen tas bort

Om en fiende når botten av skärmen:

GAME OVER visas.

TESTNING AV SPELET

För att testa spelet:

Starta programmet.

Flytta spelaren med tangenterna W, A, S och D.

Skjut projektiler med SPACE.

Kontrollera att projektiler kan träffa och förstöra fiender.

Kontrollera att fiender försvinner när de träffas.

Kontrollera att spelet visar texten "GAME OVER" när en fiende når botten av skärmen.

ÖVRIGA ANMÄRKNINGAR

Spelmotorn är designad för att kunna användas till flera spel av samma typ.

Nya spel kan skapas genom att implementera nya klasser som ärver från basklassen Sprite utan att behöva ändra spelmotorns kod.

Detta demonstrerar användning av objektorienterad design med arv och polymorfism.