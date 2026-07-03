# TODO List

- [ ] Fix sprites phasing through walls on low FPS.
    - Instead of checking collision only at future position, check collision between current and future position.
- [ ] Improve friction.
    - Friction is applied every frame by removing some velocity if the sprite is moving and grounded. This causes the sprite to never reach it's max speed when grounded, and get a speed boost when jumping. Is this desiered behaviour?
- [ ] Improve sprite horizontal acceleration
    - Reduce the acceleration when the sprite is not grounded, so that it is harder for sprites to change direction while mid air.
- [ ] Do something about level boundries (jumping above world height seg faults)

## Complete

- [x] Introduce tilemap asset files.
    - Compiles into a single file from a directory containing metadata and textures
    - Metadata is pulled from a text file, texture data is from 32-bit color .bmp files or .png files
- [x] Improve level format
    - Remove ASCII numbfers, now all numeric values are represented in binary