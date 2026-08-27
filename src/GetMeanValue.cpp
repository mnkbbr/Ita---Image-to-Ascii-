float GetMeanValue(const unsigned char* data, int width, int height, int i, int j, int f, int desired_size) {
    int totalvalue = 0;
    int desired_size_y = desired_size * 2;
    int frame = f * (width * height);

    int start_x =  i * desired_size;
    int start_y =  j * desired_size_y;

    for (int y = 0; y < desired_size_y; y++) {
        for (int x = 0; x < desired_size; x++) {

            int pixel_x = start_x + x;
            int pixel_y = start_y + y;

            if (pixel_x >= width || pixel_y >= height) continue;

            int pixel_index = frame + (pixel_y * width + pixel_x);

            totalvalue += (int)data[pixel_index];
        }
    }

    int pixels_count = desired_size * desired_size_y;
    return (float)totalvalue / pixels_count;
}