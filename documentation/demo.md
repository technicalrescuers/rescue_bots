# Demo #
Step 1: Central Control Unit (CCU) invokes Search Drone's (SD) REST API with search location coordinates (in cartesian form - (x, y)) and search radius (R).
Step 2: SD moves to (x, y) and searches with given radius by rotating anti-clockwise until victim (Vi) is identified.
Step 3: SD adjusts it's angle and camera's angle such that Vi is in the center of the video stream.
Step 4: SD computes the GPS location of Vi (xi, yi).
Step 5: SD returns JSON response with (xi, yi) of Vi to CCU.
Step 6: CCU invokes Rescue Drone's (RD) REST API with (xi, yi).
Step 7: RD moves to next Aid Packet (APi) and picks it up.
Step 8. RD carries APi to (xi, yi).
Step 9: RD drops APi at (xi, yi).
Step 10: RD returns to it's resting location (xr, yr).
Step 11: RD sends acknowledgment to CCU (200 OK) about successful delivery.
Step 12: CCU updates persistent store (PS) about the activity.