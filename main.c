#include <stdio.h>

int main() {
    // Open the file with "w" (write) mode to create the SVG file from scratch.
    FILE *fp = fopen("curve.svg", "w");
    if (fp == NULL) return 1;

    // These variables act as our 'settings.'
    // 'steps' controls the density of the lines, and 'gap' is the math that 
    // spreads them out evenly across the length of the 'size' variable.
    int i, centerX = 300, centerY = 300, size = 150, steps = 15;
    float gap = (float)size / steps;

    // I used an SVG group <g> to shift the (0,0) origin to the center of the screen.
    // This makes the math easier because I can treat the center as a starting point.
    fprintf(fp, "<svg width='600' height='600' xmlns='http://www.w3.org/2000/svg' style='background: #000;'>\n");
    fprintf(fp, "<g transform='translate(300,300)'>\n");

    // This loop creates the 'string art' effect.
    for (i = 0; i <= steps; i++) {
        // Connects a point on the Y-axis to a point on the X-axis. 
        // As i increases, 'offset' moves away from the center while 'invOffset' 
        // moves toward the center, creating the curved optical illusion.
        float offset = i * gap;
        float invOffset = size - (i * gap);
        
        // This takes the current loop index and maps it to a 360-degree color wheel.
        // It ensures the star cycles through the full HSL rainbow as it iterates.
        float hue = ((float)i / steps) * 360;

        // I'm drawing the curve four times, one for each quadrant of the screen.
        // Each line uses a mix of offset and invOffset to stay aligned with the axes.

        // Top-Right Quadrant: Y is negative (up), X is positive (right).
        fprintf(fp, "<line x1='0' y1='%f' x2='%f' y2='0' stroke='hsl(%f, 100%%, 50%%)' stroke-width='1.2' />\n", -invOffset, offset, hue);
        
        // Top-Left Quadrant: Both X and Y are negative to move up and left.
        fprintf(fp, "<line x1='0' y1='%f' x2='%f' y2='0' stroke='hsl(%f, 100%%, 50%%)' stroke-width='1.2' />\n", -invOffset, -offset, hue);
        
        // Bottom-Left Quadrant: Y is positive (down), X is negative (left).
        fprintf(fp, "<line x1='0' y1='%f' x2='%f' y2='0' stroke='hsl(%f, 100%%, 50%%)' stroke-width='1.2' />\n", invOffset, -offset, hue);
        
        // Bottom-Right Quadrant: Both X and Y are positive.
        fprintf(fp, "<line x1='0' y1='%f' x2='%f' y2='0' stroke='hsl(%f, 100%%, 50%%)' stroke-width='1.2' />\n", invOffset, offset, hue);
    }

    // Wrap up the file by closing the SVG tag and the file stream.
    fprintf(fp, "</g>\n</svg>");
    fclose(fp);
    
    //Confirmation that the progam ran
    printf("Successfully created 'curve.svg' containing only the star!\n");
    return 0;
}
