#include <iostream>
#include <fstream>

using namespace std;

float driven_total(float);
float driven_side(float, float);
float reflector(float);
float directors(float);
float driven_spacing(float);
float initial_director_spacing(float);
float directors_spacing(float);
void generate_datasheet(int num_elements, float frequency, float gap, float driven_length, float driven_side_length,float reflector_length, float director_length, float driven_pos, float in_director_pos,float director_space, float Gain_dBd, float Gain_dBi);





int main()
{
	int num_elements = 3;
	char exit;
	float gap, frequency, wavelength, driven_length, reflector_length, director_length, driven_side_length, reflector_pos = 0, driven_pos, in_director_pos, director_space;

	cout << "----Yagi-Uda Antenna Calculator---" << endl << endl;
	cout << "Please enter the desired frequency you want your antenna to operate on(MHz): ";
	cin >> frequency;
	cout << "Please enter the size of the gap between the driven dipole elements (default 1.0 inch (0.025m))" << endl << "For default length press 0: ";
	cin >> gap;
	if (gap == 0)
	{
		gap = 0.025;
	}
	do {
		cout << "Please enter the number of element (3+): ";
		cin >> num_elements;
	} while (num_elements < 3);
	wavelength = 300 / frequency;

	driven_length = driven_total(wavelength);
	driven_side_length = driven_side(driven_length, gap);
	reflector_length = reflector(driven_length);
	director_length = directors(driven_length);
	driven_pos = driven_spacing(wavelength);
	in_director_pos = initial_director_spacing(wavelength);
	director_space = directors_spacing(wavelength);
	float Gain_dBd = 2 + (num_elements - 2);
	float Gain_dBi = Gain_dBd + 2.15;

	system("cls");

	cout << "----Yagi-Uda Antenna Calculator---" << endl << endl;
	cout << "Antenna Specifications: " << endl;
	cout << " Number of elements: " << num_elements << endl;
	cout << " frequency: " << frequency << endl;
	cout << " approximate gain(dBd): " << Gain_dBd << endl;
	cout << " approximate gain(dBi): " << Gain_dBi << endl;
	cout << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Element dimensions:" << endl;
	cout << " Reflector: " << reflector_length << "m, " << reflector_length * 100 << "cm" << endl;
	cout << " Driven Total: " << driven_length << "m, " << driven_length * 100 << "cm" << endl;
	cout << " Driven side: " << driven_side_length << "m, " << driven_side_length * 100 << "cm" << endl;
	cout << " Gap between driven dipole: " << gap << "m, " << gap * 1000 << "mm" << endl;
	cout << " Director(s): " << director_length << "m, " << director_length * 100 << "cm" << endl;
	cout << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Element positioning relative to reflector" << endl;
	cout << " Driven: +" << driven_pos << endl;
	cout << " Initial Director: +" << in_director_pos << endl;
	cout << " Other directors (spacing from each other): +" << director_space << endl;
	cout << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Tip: Please feel free to play around with the spacing between the elements to match your impendance perfectly" << endl;
	cout << "Tip2: The length of the elements doesn't need to be exact, the closer it is the better." << endl;
	cout << "Tip3: You need to connect the middle cable of the coax to one side of the dipole and the ground to the other." << endl;
	cout << "Tip4: Use thick wire to connect the two side elements from the opposite side of your coax, this shouldn't be more than 7-9 cm long";
	cout << endl << endl << endl;
	cout << "Do you want to generate datasheet and exit? (y/n)" << endl;
	do {
		cin >> exit;
	} while (exit != 'y' && exit != 'n');
	if (exit == 'y') {
		generate_datasheet(num_elements, frequency, gap, driven_length, driven_side_length, reflector_length, director_length, driven_pos, in_director_pos, director_space, Gain_dBd, Gain_dBi);

	}
}
float driven_total(float wavelength)
{
	return 0.47 *wavelength;
}
float driven_side(float driven_length_total, float gap)
{
	return (driven_length_total - gap) / 2;
}
float reflector(float driven_length)
{
	return 1.05 * driven_length;
}
float directors(float driven_length)
{
	return 0.95 * driven_length;
}
float driven_spacing(float wavelength)
{
	return 0.2 * wavelength;
}
float initial_director_spacing(float wavelength)
{
	return 0.15 * wavelength + driven_spacing(wavelength);
}
float directors_spacing(float wavelength)
{
	return 0.2 * wavelength;
}
void generate_datasheet(int num_elements, float frequency, float gap, float driven_length, float driven_side_length,
	float reflector_length, float director_length, float driven_pos, float in_director_pos,
	float director_space, float Gain_dBd, float Gain_dBi)
{
	ofstream datasheet("antenna_datasheet.txt");
	datasheet << "----Yagi-Uda Antenna Calculator---" << endl << endl;

	datasheet << "Antenna Specifications: " << endl;
	datasheet << " Number of elements: " << num_elements << endl;
	datasheet << " frequency: " << frequency << endl;
	datasheet << " approximate gain(dBd): " << Gain_dBd << endl;
	datasheet << " approximate gain(dBi): " << Gain_dBi << endl;
	datasheet << endl;
	datasheet << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	datasheet << "Element dimensions:" << endl;
	datasheet << " Reflector: " << reflector_length << "m, " << reflector_length * 100 << "cm" << endl;
	datasheet << " Driven Total: " << driven_length << "m, " << driven_length * 100 << "cm" << endl;
	datasheet << " Driven side: " << driven_side_length << "m, " << driven_side_length * 100 << "cm" << endl;
	datasheet << " Gap between driven dipole: " << gap << "m, " << gap * 1000 << "mm" << endl;
	datasheet << " Director(s): " << director_length << "m, " << director_length * 100 << "cm" << endl;
	datasheet << std::endl;
	datasheet << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	datasheet << "Element positioning relative to reflector" << endl;
	datasheet << " Driven: +" << driven_pos << endl;
	datasheet << " Initial Director: +" << in_director_pos << endl;
	datasheet << " Other directors (spacing from each other): +" << director_space << endl;
	datasheet.close();

}
