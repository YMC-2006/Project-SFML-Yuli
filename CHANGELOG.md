# 🧾 CHANGELOG

Este archivo documenta los cambios más importantes realizados a lo largo del desarrollo del proyecto **Match-3 Game** en C++ con SFML.  
Cada versión corresponde a una etapa del proyecto evaluada durante el curso.

---

## [v1.0] — Primera Entrega  
📅 **Fecha de entrega:** 10 de setiembre de 2025  
🏆 **Nota obtenida:** 100 / 100  

### ✨ Nuevas funcionalidades:
- Se crearon los sprites base de gemas normales.
- Se desarrollaron las clases principales del juego:
  - `Game`
  - `Board`
  - `Gem`
- Se implementó la generación aleatoria de gemas dentro del tablero.
- Se estructuró el proyecto en archivos `.h` y `.cpp` separados para cada clase.
- El juego es funcional, pero aún **no incluye animaciones**.

---

## [v2.0] — Segunda Entrega  
📅 **Fecha de entrega:** 15 de octubre de 2025  
🏆 **Nota obtenida:** 100 / 100  

### ✨ Nuevas funcionalidades y mejoras:
- Se añadieron animaciones principales:
  - Gravedad (caída de gemas).
  - Intercambio de posiciones (swap).
  - Eliminación con efecto visual (*fade-out*).
- Se implementaron dos nuevos tipos de gemas especiales:
  - `BombGem` — Se genera aleatoriamente, tiene comportamiento especial.
  - `IceGem` — Representa una gema con "hielo", con lógica específica.
- Cada gema ahora tiene un método virtual que define cuántos puntos otorga.
- Se añadieron **5 niveles jugables** al sistema.
- Nueva estructura `LevelConfig.h` encargada de definir los atributos de cada nivel.
- El proyecto ahora contiene 5 clases principales:
  - `Game`, `Board`, `Gem`, `BombGem`, `IceGem`

---

## [v3.0] — Tercera Entrega (Final)  
📅 **Fecha de entrega:** _Pendiente_  
🏁 **Nota:** _Por evaluar_  

### ✨ Nuevas funcionalidades y mejoras:
- Se implementó un sistema de **ranking local** (puntuaciones y nombres de usuario).
- Sistema de **niveles bloqueados y desbloqueados**, según progreso del jugador.
- Persistencia de datos con archivos: el juego recuerda el progreso aún después de cerrar.
- Nuevas funciones implementadas:
  - `swapBooster`: permite intercambiar gemas libremente como ventaja.
  - Manejo de usuario con creación y registro.
- Corrección de errores en el comportamiento y visualización de la barra de progreso.
- Las **gemas bomba** ahora se generan dinámicamente cuando se hace un match de más de 4 gemas consecutivas (¡nuevo comportamiento inteligente!).

---
