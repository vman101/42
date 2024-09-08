#include <mlx.h>
#include <math.h>
#include <stdint.h>

void draw_gradient(void *mlx_ptr, void *win_ptr) {
    int width = 800;
    int height = 600;
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Example: calculating color based on normalized x and y positions
            float r_f = (float)x / (float)width;
            float g_f = (float)y / (float)height;
            float b_f = 0.5;  // Static blue component
            
            // Convert to 0-255 range
            int r = (int)(r_f * 255);
            int g = (int)(g_f * 255);
            int b = (int)(b_f * 255);
            
            // Combine into a 32-bit RGB color
            int color = (r << 16) | (g << 8) | b;
            
            // Draw the pixel
            mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
        }
    }
}

int main() {
    void *mlx_ptr = mlx_init();
    void *win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Gradient");

    draw_gradient(mlx_ptr, win_ptr);

    mlx_loop(mlx_ptr);
    return 0;
}
