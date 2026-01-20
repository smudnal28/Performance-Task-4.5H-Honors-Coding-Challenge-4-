#include <stdio.h>

int main() {
    FILE *fp = fopen("curve.svg", "w");
    if (fp == NULL) return 1;

    // size = 150 (the length of the axes from your Snap! script)
    // steps = 15 (matching your 'for i = 1 to 15' loop)
    int i, centerX = 300, centerY = 300, size = 150, steps = 15;
    float gap = (float)size / steps;

    // Start SVG file with a black background
    fprintf(fp, "<svg width='600' height='600' xmlns='http://www.w3.org/2000/svg' style='background: #000;'>\n");
    fprintf(fp, "<g transform='translate(300,300)'>\n");

    // DRAW THE CENTRAL STAR (Quadrants 1-4 Only)
    for (i = 0; i <= steps; i++) {
        float offset = i * gap;
        float invOffset = size - (i * gap);
        
        // Rainbow color effect using HSL
        float hue = ((float)i / steps) * 360;

        // Top-Right Quadrant
        fprintf(fp, "<line x1='0' y1='%f' x2='%f' y2='0' stroke='hsl(%f, 100%%, 50%%)' stroke-width='1.2' />\n", -invOffset, offset, hue);
        
        // Top-Left Quadrant
        fprintf(fp, "<line x1='0' y1='%f' x2='%f' y2='0' stroke='hsl(%f, 100%%, 50%%)' stroke-width='1.2' />\n", -invOffset, -offset, hue);
        
        // Bottom-Left Quadrant
        fprintf(fp, "<line x1='0' y1='%f' x2='%f' y2='0' stroke='hsl(%f, 100%%, 50%%)' stroke-width='1.2' />\n", invOffset, -offset, hue);
        
        // Bottom-Right Quadrant
        fprintf(fp, "<line x1='0' y1='%f' x2='%f' y2='0' stroke='hsl(%f, 100%%, 50%%)' stroke-width='1.2' />\n", invOffset, offset, hue);
    }

    fprintf(fp, "</g>\n</svg>");
    fclose(fp);
    
    printf("Successfully created 'curve.svg' containing only the star!\n");
    return 0;
}