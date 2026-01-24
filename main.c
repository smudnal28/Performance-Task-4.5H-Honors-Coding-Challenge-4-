#include <stdio.h>

// PROJECT: CURVE STITCHING

int main() {
    
    // We establish a 'FILE' pointer to handle the output stream to the disk.
    // 'fopen' with "w" mode creates a new file, allowing the program to write raw XML/SVG instructions directly from the logic.
    FILE *fp = fopen("curve.svg", "w");
    if (fp == NULL) return 1;

    // 'steps' controls the line density; 'size' defines the axial magnitude.
    // I applied an explicit (float) type cast to 'size' to ensure that the division for 'gap' remains precise and avoids integer truncation errors.
    int i, centerX = 300, centerY = 300, size = 150, steps = 15;
    float gap = (float)size / steps;

    // Digital displays use a top-left origin (0,0). I used an SVG group <g> with a 'translate' transform to shift our logical origin to the center.
    // This allows for symmetrical Cartesian plotting across all four quadrants.
    fprintf(fp, "<svg width='600' height='600' xmlns='http://www.w3.org/2000/svg' style='background: #000;'>\n");
    fprintf(fp, "<g transform='translate(300,300)'>\n");

    // This 'for' loop acts as the procedural engine, calculating the specific vertices for every line based on the current iteration 'i'.
    for (i = 0; i <= steps; i++) {
        
        // To create the curve, we connect points that move in opposite directions.
        // 'offset' increases with the loop, while 'invOffset' decreases.
        // This inverse relationship defines the geometry of the parabolic envelope.
        float offset = i * gap;
        float invOffset = size - (i * gap);
        
        // Instead of RGB, I used HSL (Hue, Saturation, Lightness).
        // By normalizing 'i' (dividing it by steps) and multiplying by 360, we map the loop progress to the degrees of the color wheel.
        float hue = ((float)i / steps) * 360;

        // Cartesian Quadrant Plotting:
        // We project the calculated points across all four quadrants by manipulating the positive/negative signs of the X and Y coordinates.

        // Top-Right: Positive X, Negative Y (Displacement Up)
        fprintf(fp, "<line x1='0' y1='%f' x2='%f' y2='0' stroke='hsl(%f, 100%%, 50%%)' stroke-width='1.2' />\n", -invOffset, offset, hue);
        
        // Top-Left: Negative X, Negative Y (Displacement Up/Left)
        fprintf(fp, "<line x1='0' y1='%f' x2='%f' y2='0' stroke='hsl(%f, 100%%, 50%%)' stroke-width='1.2' />\n", -invOffset, -offset, hue);
        
        // Bottom-Left: Negative X, Positive Y (Displacement Down/Left)
        fprintf(fp, "<line x1='0' y1='%f' x2='%f' y2='0' stroke='hsl(%f, 100%%, 50%%)' stroke-width='1.2' />\n", invOffset, -offset, hue);
        
        // Bottom-Right: Positive X, Positive Y (Displacement Down/Right)
        fprintf(fp, "<line x1='0' y1='%f' x2='%f' y2='0' stroke='hsl(%f, 100%%, 50%%)' stroke-width='1.2' />\n", invOffset, offset, hue);
    }

    // Closing the XML tags and the file stream ensures all buffered data is written to the disk correctly and system memory is released.
    fprintf(fp, "</g>\n</svg>");
    fclose(fp);
    
    printf("Successfully created 'curve.svg'.\n");
    return 0;
}
