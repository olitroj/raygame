# TODO List

- [ ] Have numbers represented in binary in asset files.
    - Instead of representing numbers as ASCII digits, have them represented in binary to reduce asset file size.
- [ ] Introduce tilemap asset files.
    - Compiles into a single file from a directory containing a metadata text file and same-sized PNG texture files.
- [ ] Fix sprites phasing through walls on low FPS.
    - Instead of checking collision only at future position, check collision between current and future position.
- [ ] Improve friction.
    - Friction is applied every frame by removing some velocity if the sprite is moving and grounded. This causes the sprite to never reach it's max speed when grounded, and get a speed boost when jumping. Is this desiered behaviour?
- [ ] Have sprite horizontal acceleration time depend on current gravity.