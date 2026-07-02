# TODO List

- [ ] Fix sprites phasing through walls on low FPS.
    - Instead of checking collision only at future position, check collision between current and future position.
- [ ] Improve friction.
    - Friction is applied every frame by removing some velocity if the sprite is moving and grounded. This causes the sprite to never reach it's max speed when grounded, and get a speed boost when jumping. Is this desiered behaviour?
- [ ] Improve sprite horizontal acceleration
    - Reduce the acceleration when the sprite is not grounded, so that it is harder for sprites to change direction while mid air.
- [ ] Do something about level boundries (jumping above world height seg faults)

## Complete

- [x] Have numbers represented in binary in asset files.
    - I cannot use a null-termination byte when representing binary numbers because 0 is also used in binary representation. I would either have to make all integers in the file a fixed byte size, or add metadata that outlines how many bytes each integer gets. So I sticked to the ASCII digits.
    - I did use binary representation for the tilemap, since one byte can contain up to 256 different tiles (including air).
- [x] Introduce tilemap asset files.
    - Compiles into a single file from a directory containing metadata and raw color data
    - Metadata is pulled from a text file, color data pulled from 32-bit color .bmp files