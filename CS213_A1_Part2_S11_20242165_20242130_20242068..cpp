//FILE: CS213_A1_Part2_sec11_20242068_20242130_20242165

//Section: 11
// Names and IDs:

//ID: 20242068 => Aya Mohammad Mohammad
//ID: 20242130 => Rawan Youssry Ebrahim
//ID: 20242165 => Salma Mohammed Bahi El_deen Selim


//Filters distribution:

//20242068 : Filter 1: gray scale, Filter 4: merge 2 images, Filter 7: darken and lighten image,Filter 10:detect edges, Filter 13: Sunlight
//20242130 : Filter 2: Black and white, Filter 5: Flipping images,Filter 8: crop the image, Filter 11: Resize the image, Filter 14: Puple image
//20242165 : Filter 3: Invert images, Filter 6: Rotate image,Flter 9: Adding a frame to the picture,Filter 12: Blur image,Filter 15: Infrared photography


#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>


using namespace std;
#include "Image_Class.h"

int Save = 1;
int Exit = 0;
string filename, file1, file2;
int choose = 0;

enum enFilter {
	grayscale = 1, Black_and_white = 2, Invert_images = 3, merge_2_images = 4, Flip_image = 5, Rotate_the_image = 6, darken_and_lighten_image = 7, Crop_image = 8, Adding_a_frame_to_the_photo = 9, detect_edges = 10, Resize_image = 11, Blur_Image = 12, sunlight = 13, Purple_Wano = 14, Infrared_photography = 15,
};

void Choices()
{
	
	cout << "\n**********************************************\n";
	cout << "**********************************************\n\n";
	
	cout << "Filter 1: Convert image to Gray scale\n";
	cout << "Filter 2: Convert image to Black and white\n";
	cout << "Filter 3: Invert images\n";
	cout << "Filter 4: Merge 2 images\n";
	cout << "Filter 5: Flip the image:\n  1- Vertically\n  2- Horizontally \n";
	cout << "Filter 6: Rotate image\n  1- 90 Degree\n  2- 180 Degree\n  3- 270 Degree\n";
	cout << "Filter 7: darken and lighten image\n";
	cout << "Filter 8: Crop the image\n";
	cout << "Filter 9: Adding a frame to the picture\n";
	cout << "Filter 10: Detect edges\n";
	cout << "Filter 11: Resize the image\n";
	cout << "Filter 12: Blur images\n";
	cout << "Filter 13: Sunlight\n";
	cout << "Filter 14: Purple image\n";
	cout << "Filter 15: Infrared photography\n";

	cout << "\n**********************************************\n";
	cout << "**********************************************\n\n";
	cout << "Please choose what you want: ";
}

void SaveFunction(Image& image, string& filename)
{

	cout << "Do you want to save changes?\n";
	cout << "(1) Yes\n";
	cout << "(2) No\n";
	cin >> Save;
	if (Save == 1)
	{
		cout << "Please choose:\n";
		cout << "(1) Save at the same file\n";
		cout << "(2) Save at new file\n";

		int choose;
		cin >> choose;

		switch (choose)
		{
		case 1:
			image.saveImage(filename);
			break;
		case 2:
			cout << "Please enter image name to store new image and and specify extension .jpg, .bmp, .png, .tga: \n";

			cin >> filename;

			image.saveImage(filename);
			break;
		default:
			cout << "Invalid choice\n";
			break;
		}
	}
}

void ExitFunction(Image& image, string& filename)
{
	if (Exit == true)
	{
		Image image(filename);
		SaveFunction(image, filename);
	}

}

void gray_scale(Image& image, string& filename)
{
	for (int w = 0; w < image.width; ++w)
	{
		for (int h = 0; h < image.height; ++h)
		{
			unsigned avg = 0;
			for (int c = 0; c < 3; ++c)
			{
				avg += image(w, h, c);
			}
			avg /= 3;
			image(w, h, 0) = avg;
			image(w, h, 1) = avg;
			image(w, h, 2) = avg;
		}
	}
	SaveFunction(image, filename);
	system(filename.c_str());
}

void BlackAndWhite(Image& image, string& filename)
{

	for (int i = 0; i < image.width; ++i) {
		for (int j = 0; j < image.height; ++j) {
			unsigned  int avg = 0;

			for (int k = 0; k < 3; ++k)
			{
				avg += image(i, j, k);
			}

			avg /= 3;
			if (avg >= 127)
			{
				image(i, j, 0) = 255;
				image(i, j, 1) = 255;
				image(i, j, 2) = 255;
			}
			else
			{
				image(i, j, 0) = 0;
				image(i, j, 1) = 0;
				image(i, j, 2) = 0;
			}

		}
	}
	SaveFunction(image, filename);
	system(filename.c_str());
}

void InvertImages(Image& image, string& filename)
{
	for (int x = 0; x < image.width; ++x)
	{
		for (int y = 0; y < image.height; ++y)
		{
			image(x, y, 0) = 255 - image(x, y, 0);
			image(x, y, 1) = 255 - image(x, y, 1);
			image(x, y, 2) = 255 - image(x, y, 2);
		}
	}
	SaveFunction(image, filename);
	system(filename.c_str());
}

void Merge2images(Image& image, string& filename)
{
	string file2;
	cout << "Enter the name of the second image\n";
	cin >> file2;

	Image image1 = image;
	Image image2(file2);

	Image newImage(1, 1);
	int newWidth = 0, newHeight = 0;

	
	if (image1.height == image2.height && image1.width == image2.width)
	{
		newWidth = image1.width;
		newHeight = image1.height;
		newImage = Image(newWidth, newHeight);
	}
	else
	{
		cout << "Select merge type:\n";
		cout << "1 - Resize smaller image(s) to match the largest size and merge\n";
		cout << "2 - Merge the common area only\n";
		int choice;
		cin >> choice;

		if (choice == 1)
		{
			newWidth = max(image1.width, image2.width);
			newHeight = max(image1.height, image2.height);
			newImage = Image(newWidth, newHeight);
		}
		else if (choice == 2)
		{
			newWidth = min(image1.width, image2.width);
			newHeight = min(image1.height, image2.height);
			newImage = Image(newWidth, newHeight);
		}
		else
		{
			cout << "Invalid choice\n";
			return;
		}
	}

	for (int h = 0; h < newHeight; h++)
	{
		for (int w = 0; w < newWidth; w++)
		{
			int x1 = (int)((float)w / newWidth * image1.width);
			int y1 = (int)((float)h / newHeight * image1.height);
			int x2 = (int)((float)w / newWidth * image2.width);
			int y2 = (int)((float)h / newHeight * image2.height);

			for (int c = 0; c < 3; c++)
			{
				unsigned char temp = 0;
				if (y1 < image1.height && x1 < image1.width)
					temp += image1(x1, y1, c) / 2;

				if (y2 < image2.height && x2 < image2.width)
					temp += image2(x2, y2, c) / 2;

				newImage(w, h, c) = temp;
			}
		}
	}

	newImage.saveImage(filename);
	SaveFunction(newImage, filename);
	system(filename.c_str());
}

void FlipImage(Image& image, string& filename)
{

	cout << "\n\nplease Choose what you want: \n(1) Vertically \n(2) Horizontally\n\n";
	int Choose;
	cin >> Choose;

	switch (Choose)
	{
	case 1:
		for (int i = 0; i < image.width; ++i) {
			for (int j = 0; j < image.height / 2; ++j) {
				for (int k = 0; k < 3; ++k) {
					unsigned int temp = image(i, j, k);
					image(i, j, k) = image(i, image.height - 1 - j, k);
					image(i, image.height - 1 - j, k) = temp;
				}
			}
		}

		SaveFunction(image, filename);
		system(filename.c_str());
		break;
	case 2:

		for (int i = 0; i < image.width / 2; ++i) {
			for (int j = 0; j < image.height; ++j) {
				for (int k = 0; k < 3; ++k) {
					unsigned int temp2 = image(i, j, k);
					image(i, j, k) = image(image.width - 1 - i, j, k);
					image(image.width - 1 - i, j, k) = temp2;
				}
			}
		}
		SaveFunction(image, filename);
		system(filename.c_str());
		break;
	default:
		cout << "Invalid choose\n";
		break;
	}
}

void RotateImage(Image& image, string& filename)
{
	int angle;
	cout << "Enter rotation angle (90, 180, 270): ";
	cin >> angle;

	Image temp;

	if (angle == 90)
	{
		temp = Image(image.height, image.width);
		for (int i = 0; i < image.width; i++)
			for (int j = 0; j < image.height; j++)
				for (int k = 0; k < 3; k++)
					temp(image.height - 1 - j, i, k) = image(i, j, k);
	}
	else if (angle == 180)
	{
		temp = Image(image.width, image.height);
		for (int i = 0; i < image.width; i++)
			for (int j = 0; j < image.height; j++)
				for (int k = 0; k < 3; k++)
					temp(image.width - 1 - i, image.height - 1 - j, k) = image(i, j, k);
	}
	else if (angle == 270)
	{
		temp = Image(image.height, image.width);
		for (int i = 0; i < image.width; i++)
			for (int j = 0; j < image.height; j++)
				for (int k = 0; k < 3; k++)
					temp(j, image.width - 1 - i, k) = image(i, j, k);
	}
	else
	{
		cout << "Invalid angle.\n";
		return;
	}

	image = temp;
	cout << "Rotation applied successfully (clockwise).\n";

	SaveFunction(image, filename);
	system(filename.c_str());
}

void ResizingImages(Image& image, string& filename)
{
	int NewWidth, NewHight;
	cout << "Please enter new dimentions?\n";
	cin >> NewWidth >> NewHight;

	float ScaleW = (float)image.width / NewWidth;
	float ScaleH = (float)image.height / NewHight;

	int Channels = image.channels;

	unsigned char* newData = new unsigned char[NewWidth * NewHight * Channels];

	for (int i = 0; i < NewWidth; i++)
	{
		for (int j = 0; j < NewHight; j++)
		{
			for (int c = 0; c < image.channels; c++)
			{
				int Old_I = int(i * ScaleW);
				int Old_J = int(j * ScaleH);

				if (Old_I >= image.width)
				{
					Old_I = image.width - 1;
				}

				if (Old_J >= image.height)
				{
					Old_J = image.height - 1;
				}

				int oldIndex = (Old_J * image.width + Old_I) * Channels;
				int newIndex = (j * NewWidth + i) * Channels;
				newData[newIndex + c] = image.imageData[oldIndex + c];

			}
		}
	}

	image.imageData = newData;
	image.width = NewWidth;
	image.height = NewHight;;

	SaveFunction(image, filename);
	system(filename.c_str());
}

void BlurFilter(Image& image, string& filename)
{
	int strength;
	cout << "Enter blur strength (odd number, e.g. 15, 21, 25): \n";
	cin >> strength;

	if (strength % 2 == 0) strength++;
	int offset = strength / 2;

	Image temp = image;

	for (int i = offset; i < image.width - offset; i++)
	{
		for (int j = offset; j < image.height - offset; j++)
		{
			for (int k = 0; k < 3; k++) {
				int sum = 0;
				int count = 0;

				for (int x = -offset; x <= offset; x++)
				{
					for (int y = -offset; y <= offset; y++)
					{
						sum += image(i + x, j + y, k);
						count++;
					}
				}

				temp(i, j, k) = sum / count;
			}
		}
	}
	image = temp;
	cout << "Blur applied.\n";

	SaveFunction(image, filename);
	system(filename.c_str());

}

void LightenOrDarkenImage(Image& image, string& filename)
{
	string choice;
	cout << "select 1: to lighten, 2: to darken" << endl;
	cin >> choice;

	int width = image.width;
	int height = image.height;

	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			unsigned char r = image.getPixel(w, h, 0);
			unsigned char g = image.getPixel(w, h, 1);
			unsigned char b = image.getPixel(w, h, 2);

			if (choice == "1")
			{
				r = min(255, int(1.5 * r));
				g = min(255, int(1.5 * g));
				b = min(255, int(1.5 * b));
			}
			else if (choice == "2")
			{
				r = int(r * 0.5);
				g = int(g * 0.5);
				b = int(b * 0.5);
			}
			else
			{
				cout << "invalid choice" << endl;
				return;
			}

			image.setPixel(w, h, 0, r);
			image.setPixel(w, h, 1, g);
			image.setPixel(w, h, 2, b);
		}
	}

	SaveFunction(image, filename);
	system(filename.c_str());
}

void CroppingImage(Image& image, string& filename)
{
	int W, H;
	cout << "Please specify the dimensions to crop to (smaler than or equal to the original dimentions)?\n";
	cin >> W >> H;

	if (W > image.width || H > image.height)
	{
		cout << "Invalid dimentions!\n";
	}
	else if (W == image.width && H == image.height)
	{
		SaveFunction(image, filename);
		system(filename.c_str());
	}
	else
	{
		int x, y, channels = image.channels;
		cout << "Please enter dimentuins of upper left corner of the part to keep\n";
		cin >> x >> y;

		unsigned char* newData = new unsigned char[W * H * channels];

		for (int j = y; j < (H + y); ++j)
		{
			for (int i = x; i < (W + x); ++i)
			{
				for (int c = 0; c < channels; c++)
				{
					int OldIndex = (j * image.width + i) * channels + c;
					int NewIndex = ((j - y) * W + (i - x)) * channels + c;

					newData[NewIndex] = image.imageData[OldIndex];

				}
			}
		}

		image.imageData = newData;
		image.width = W;
		image.height = H;;

		SaveFunction(image, filename);
		system(filename.c_str());
	}

}

void FrameImage(Image& image, string& filename)
{
	int thickness;
	int choice, style;
	cout << "Enter frame thickness: ";
	cin >> thickness;
	cout << "Choose color: (1) Blue (2) Red (3) White: ";
	cin >> choice;
	cout << "Choose style: (1) Simple (2) Decorated: ";
	cin >> style;

	int newWidth = image.width + 2 * thickness;
	int newHeight = image.height + 2 * thickness;
	Image framed(newWidth, newHeight);

	unsigned char r = 0, g = 0, b = 255; // Default Blue
	if (choice == 2) { r = 255; g = 0; b = 0; }       // Red
	else if (choice == 3) { r = 255; g = 255; b = 255; } // White

	for (int i = 0; i < newWidth; i++)
	{
		for (int j = 0; j < newHeight; j++)
		{
			bool isFrame = (i < thickness || j < thickness ||
				i >= image.width + thickness || j >= image.height + thickness);

			if (isFrame)
			{
				if (style == 1)
				{
					// Simple frame
					framed(i, j, 0) = r;
					framed(i, j, 1) = g;
					framed(i, j, 2) = b;
				}
				else
				{
					// Decorated frame
					if ((i / 10 + j / 10) % 2 == 0)
					{
						framed(i, j, 0) = r;
						framed(i, j, 1) = g;
						framed(i, j, 2) = b;
					}
					else
					{
						framed(i, j, 0) = 255 - r;
						framed(i, j, 1) = 255 - g;
						framed(i, j, 2) = 255 - b;
					}
				}
			}
			else
			{
				// Copy original image to the center
				for (int k = 0; k < 3; k++)
					framed(i, j, k) = image(i - thickness, j - thickness, k);
			}
		}
	}

	image = framed;
	cout << "Frame applied successfully.\n";

	SaveFunction(image, filename);
	system(filename.c_str());
}

void EdgeDetection(Image& image, string& filename)
{
	for (int w = 0; w < image.width; ++w)
	{
		for (int h = 0; h < image.height; ++h)
		{
			unsigned int avg = 0;

			for (int c = 0; c < 3; ++c)
			{
				avg += image(w, h, c);
			}

			avg /= 3;

			if (avg >= 127)
			{
				image(w, h, 0) = 255;
				image(w, h, 1) = 255;
				image(w, h, 2) = 255;
			}
			else
			{
				image(w, h, 0) = 0;
				image(w, h, 1) = 0;
				image(w, h, 2) = 0;
			}
		}
	}

	Image newimage(image.width, image.height);

	for (int w = 1; w < image.width; ++w)
	{
		for (int h = 1; h < image.height; ++h)
		{
			unsigned char current = image(w, h, 0);
			unsigned char top = image(w, h - 1, 0);
			unsigned char left = image(w - 1, h, 0);

			int difference = abs(current - left) + abs(current - top);

			unsigned char edgeColor;
			if (difference > 127)
				edgeColor = 255;
			else
				edgeColor = 0;

			for (int c = 0; c < 3; ++c)
				newimage(w, h, c) = edgeColor;
		}
	}

	SaveFunction(newimage, filename);
	system(filename.c_str());
}

void Sun_light(Image& img, string& filename)
{
	int width = img.width;
	int height = img.height;

	for (int h = 0; h < height; ++h) {
		for (int w = 0; w < width; ++w) {

			unsigned char r = img.getPixel(w, h, 0);
			unsigned char g = img.getPixel(w, h, 1);
			unsigned char b = img.getPixel(w, h, 2);

			r = min(255, int(2 * r));
			g = min(255, int(2 * g));
			b = min(255, int(1 * b));

			img.setPixel(w, h, 0, r);
			img.setPixel(w, h, 1, g);
			img.setPixel(w, h, 2, b);
		}
	}

	SaveFunction(img, filename);
	system(filename.c_str());
}

void PurpleWano(Image& image, string& filename)
{

	for (int i = 0; i < image.width; ++i)
	{
		for (int j = 0; j < image.height; ++j)
		{
			auto limit = [](int value)
				{
					if (value < 0)
					{
						return 0;
					}
					if (value > 255)
					{
						return 255;

					}
					return value;
				};

			image(i, j, 0) = limit(image(i, j, 0) * 2);
			image(i, j, 1) = limit(image(i, j, 1) / 6);
			image(i, j, 2) = limit(image(i, j, 2) * 2 + 50);
		}
	}
	SaveFunction(image, filename);
	system(filename.c_str());
}

void InfraredFilter(Image& image, string& filename)
{
	for (int i = 0; i < image.width; i++)
	{
		for (int j = 0; j < image.height; j++)
		{
			int r = image(i, j, 0);
			int g = image(i, j, 1);
			int b = image(i, j, 2);

			int ir = int(r * 2.0 + g * 0.3 - b * 0.2);
			if (ir < 0) ir = 0;
			if (ir > 255) ir = 255;

			int red = int(ir * 2.0 + 100);
			int green = int(ir * 0.4 + 50);
			int blue = int(ir * 0.3 + 40);

			if (red > 255) red = 255;
			if (green > 255) green = 255;
			if (blue > 255) blue = 255;

			int bright = (red + green + blue) / 3;

			if (bright > 160)
			{
				red = min(255, red + 60);
				green = min(255, green + 40);
				blue = min(255, blue + 30);
			}

			if (bright > 220)
			{
				red = min(255, red + 20);
				green = min(255, green + 20);
				blue = min(255, blue + 20);
			}

			image(i, j, 0) = red;
			image(i, j, 1) = green;
			image(i, j, 2) = blue;
		}
	}

	cout << "Infrared filter applied successfully.\n";
	SaveFunction(image, filename);
	system(filename.c_str());
}

void Menu(Image& image, string& filename)
{

	Choices();

	int Choose;
	cin >> Choose;

	switch (Choose)
	{
	
	case enFilter::grayscale:

		gray_scale(image, filename);
		break;

	case enFilter::Black_and_white:

		BlackAndWhite(image, filename);
		break;

	case enFilter::Invert_images:
		InvertImages(image, filename);
		break;

	case enFilter::merge_2_images:
		Merge2images(image, filename);
		break;

	case enFilter::Flip_image:

		FlipImage(image, filename);
		break;

	case enFilter::Rotate_the_image:
		RotateImage(image, filename);
		break;

	case enFilter::darken_and_lighten_image:
		LightenOrDarkenImage(image, filename);
		break;

	case enFilter::Crop_image:
		CroppingImage(image, filename);
		break;

	case enFilter::Adding_a_frame_to_the_photo:
		FrameImage(image, filename);
		break;

	case enFilter::detect_edges:
		EdgeDetection(image, filename);
		break;

	case enFilter::Resize_image:
		ResizingImages(image, filename);
		break;

	case enFilter::Blur_Image:
		BlurFilter(image, filename);
		break;

		case enFilter::sunlight:
			Sun_light(image, filename);
			break;

	case enFilter::Purple_Wano:
		PurpleWano(image, filename);
		break;

	case enFilter::Infrared_photography:
		InfraredFilter(image, filename);
		break;

	default:
		cout << "Invalid choice\n";
		break;
	}

}

int main()
{
	do
	{
		cout << "Please enter image and specify it is extention!\n";
		cin >> filename;
		Image image(filename);

		Menu(image, filename);
		cout << "\nExit?\n";
		cout << "(1) Yes\n";
		cout << "(2) No\n";
		cin >> Exit;
		if (Exit == 1) {
			ExitFunction(image, filename);
		}
	} while (Exit != 1);

}