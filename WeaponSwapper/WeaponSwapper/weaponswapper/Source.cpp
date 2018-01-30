#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;
ofstream out;
ifstream in;

bool customWeapon = false;

bool fileValid(string file)
{
	fstream kek(file);

	
	if (kek.good())
		return true;
	else
		return false;
}

string getWeaponClass(string weaponName){

	if (weaponName ==
		"WEAPON_AK47" || weaponName ==
		"WEAPON_M16" || weaponName ==
		"WEAPON_G3" || weaponName ==
		"WEAPON_G36C")
	{
		return "autorifle";
	}

	if (weaponName ==
		"WEAPON_BERETTA" || weaponName ==
		"WEAPON_USP" || weaponName ==
		"WEAPON_COLT45" || weaponName ==
		"WEAPON_DESERTEAGLE")
	{
		return "pistol";
	}

	if (weaponName ==
		"WEAPON_M40A3" || weaponName ==
		"WEAPON_REMINGTON700" || weaponName ==
		"WEAPON_M21" || weaponName ==
		"WEAPON_DRAGUNOV")
	{
		return "sniper";
	}

	if (weaponName ==
		"WEAPON_SAW" || weaponName ==
		"WEAPON_RPD" || weaponName ==
		"WEAPON_M60E4")
	{
		return "lmg";
	}

	if (weaponName ==
		"WEAPON_MP5" || weaponName ==
		"WEAPON_SKORPION" || weaponName ==
		"WEAPON_UZI" || weaponName ==
		"WEAPON_AK74U" || weaponName ==
		"WEAPON_P90")
	{
		return "smg";
	}

	if (weaponName ==
		"WEAPON_BENELLI" || weaponName ==
		"WEAPON_WINCHESTER1200")
	{
		return "shotgun";
	}

	cout << "Using autorifle as weapon type..." << endl << endl;
	return "autorifle";

}
string findAnimType(string weaponName)
{
	if (weaponName ==
		"WEAPON_AK47" || weaponName ==
		"WEAPON_M16" || weaponName ==
		"WEAPON_G3" || weaponName ==
		"WEAPON_G36C")
	{
		return "autorifle";
	}

	if (weaponName ==
		"WEAPON_BERETTA" || weaponName ==
		"WEAPON_USP" || weaponName ==
		"WEAPON_COLT45" || weaponName ==
		"WEAPON_DESERTEAGLE")
	{
		return "pistol";
	}

	if (weaponName ==
		"WEAPON_M40A3" || weaponName ==
		"WEAPON_REMINGTON700" || weaponName ==
		"WEAPON_M21" || weaponName ==
		"WEAPON_DRAGUNOV")
	{
		return "sniper";
	}

	if (weaponName ==
		"WEAPON_SAW" || weaponName ==
		"WEAPON_RPD" || weaponName ==
		"WEAPON_M60E4")
	{
		return "autorifle";
	}

	if (weaponName ==
		"WEAPON_MP5" || weaponName ==
		"WEAPON_SKORPION" || weaponName ==
		"WEAPON_UZI"|| weaponName ==
		"WEAPON_AK74U"|| weaponName ==
		"WEAPON_P90")
	{
		return "SMG";
	}

	if (weaponName ==
		"WEAPON_BENELLI" || weaponName ==
		"WEAPON_WINCHESTER1200")
	{
		return "other";
	}

	cout << "Enter animtype" << endl;

	cout << "Possible anim types:" << endl;

	customWeapon = true;

	cout << "autorifle" << endl;
	cout << "pistol" << endl;
	cout << "sniper" << endl;
	cout << "launcher" << endl;
	cout << "smg" << endl;
	cout << "rocketlauncher" << endl;
	cout << "other (for shotguns)" << endl;
	
	string type;
	cin >> type;
	return type;
}
string findWeaponName(string stuff)
{
	int pos = stuff.find("displayName") + 12;

	//cout << "found weapon name at " << pos << endl;

	int backslash = stuff.find("\\", pos);

	//cout << "found backslash name at " << backslash << endl;	
	//cout << pos << endl << backslash << endl;

	string weaponName = stuff.substr(pos, backslash-pos);

	//cout << "Weapon is " << weaponName << endl;

	return weaponName;
}

void fixAttachments(string &stuff, bool forMP = 1)
{
	int begin, end;
	cout << "remove anim...." << endl << endl;
	begin = stuff.find("playerAnimType");
	end = stuff.find("\\", begin + 16);
	if (begin != string::npos && end != string::npos){
		stuff.erase(begin, end - begin + 1);
	}

}

string findAiType(string stuff)
{
	string weaponName = findWeaponName(stuff);

	if (weaponName ==
		"WEAPON_AK47" || weaponName ==
		"WEAPON_M16" || weaponName ==
		"WEAPON_G3" || weaponName ==
		"WEAPON_G36C")
	{
		return "assault_rifle";
	}

	if (weaponName ==
		"WEAPON_BERETTA" || weaponName ==
		"WEAPON_USP" || weaponName ==
		"WEAPON_COLT45" || weaponName ==
		"WEAPON_DESERTEAGLE")
	{
		return "pistol";
	}

	if (weaponName ==
		"WEAPON_M40A3" || weaponName ==
		"WEAPON_REMINGTON700" || weaponName ==
		"WEAPON_M21" || weaponName ==
		"WEAPON_DRAGUNOV")
	{
		return "sniper_rifle";
	}

	if (weaponName ==
		"WEAPON_SAW" || weaponName ==
		"WEAPON_RPD" || weaponName ==
		"WEAPON_M60E4")
	{
		return "assault_rifle";
	}

	if (weaponName ==
		"WEAPON_MP5" || weaponName ==
		"WEAPON_SKORPION" || weaponName ==
		"WEAPON_UZI" || weaponName ==
		"WEAPON_AK74U" || weaponName ==
		"WEAPON_P90")
	{
		return "smg";
	}

	if (weaponName ==
		"WEAPON_BENELLI" || weaponName ==
		"WEAPON_WINCHESTER1200")
	{
		return "pistol";
	}

	cout << "Using assualt_rifle accuracy graph..." << endl << endl;
	return "assault_rifle";
}

void convertToSP(char *argv[], string filename, int num)
{
	fstream theFile(argv[num]);


	string file = filename;
	string stuff;

	if (theFile.is_open() && theFile.good())
	{
		getline(theFile, stuff, '='); //convert everything into a string
		cout << "*******************Converting gun for SP*******************" << endl << endl;
		//inits
		string weaponName = findWeaponName(stuff);
		cout << "weapon name is " << weaponName << endl << endl;



		int marker;
		cout << "adding accuracy stats...." << endl << endl;;
		string accuracy = findAiType(stuff);
		int insertion = stuff.find("\\modeName");
		marker = insertion + 11;
		stuff.insert(marker,"aiVsAiAccuracyGraph\\");
		marker += 20;
		stuff.insert(marker,accuracy);
		marker += accuracy.length();
		stuff.insert(marker,".accu\\");
		marker += 6;
		stuff.insert(marker,"aiVsPlayerAccuracyGraph\\");
		marker += 24;
		stuff.insert(marker,accuracy);
		marker += accuracy.length();
		stuff.insert(marker,".accu\\");

		//

		fixAttachments(stuff,0);

		//if (file.find("_mp"))
		//	file.erase(file.find("_mp"), 3);

		string newFile = file;
		out.open(newFile, ios::out);
		out << stuff;


		out.close();
		theFile.close();

		cout << "wrote to " << newFile << endl;
		cout << "Done." << endl;
	}
	else
	{
		cout << file << " doesn't exist :(" << endl;
	}

	//cout << stuff << endl;

}

void convertToMP(string file)
{

	//broken probably LOL

	fstream theFile(file);

	string stuff;

	if (theFile.is_open() && theFile.good())
	{
		getline(theFile, stuff,'='); //convert everything into a string
		//inits
		string weaponName = findWeaponName(stuff);
		cout << "*******************Converting gun for MP*******************" << endl;
		cout << "weapon name is " << weaponName << endl << endl;

		string animType = findAnimType(weaponName);

		cout << "weapon anim type is " << animType << endl << endl;



		//anim type adder
		cout << "animtype...." << endl;
		int marker = stuff.find("modeName\\\\") + 10;

		stuff.insert(marker, "playerAnimType\\");
		marker = marker + 15;
		stuff.insert(marker, animType);
		marker += animType.length();
		stuff.insert(marker, "\\");


		//gun model converter
		if (!customWeapon){
			cout << "gunmodel...." << endl <<endl;
			string gunModelstring = "gunModel\\viewmodel_";
			marker = stuff.find(gunModelstring) + gunModelstring.length();
			marker = stuff.find("\\", marker);
			stuff.insert(marker, "_mp");
		}
		else
		{
			char response;
			cout << "Is this a vanilla weapon?" << endl;

			cin >> response;

			if (response == 'y')
			{
				cout << "gunmodel...." << endl << endl;
				string gunModelstring = "gunModel\\viewmodel_";
				marker = stuff.find(gunModelstring) + gunModelstring.length();
				marker = stuff.find("\\", marker);
				stuff.insert(marker, "_mp"); //append _mp to end of gunmodel name
			}

		}

		fixAttachments(stuff);


		string newFile = file + "_mp";
		out.open(newFile, ios::out);
		out << stuff;


		out.close();
		theFile.close();

		cout << "wrote to " << newFile << endl;
	}
	else
	{
		cout << file << " doesn't exist :(" << endl;
	}

	//cout << stuff << endl;

}

void convertAllMPGuns()
{
	//string gunList[] = { "ak47_mp", "m16_mp", "g3_mp", "g36c_mp", "mp5_mp", "skorpion_mp", "uzi_mp", "ak74u_mp", "p90_mp", "saw_mp", "rpd_mp", "m60e4_mp", "m1014_mp", "winchester1200_mp", "m40a3_mp", "remington700_mp", "dragunov_mp", "beretta_mp", "usp_mp", "colt45_mp", "deserteagle_mp" };

	//for (int i = 0; i < 21; i++)
	//{
	//	convertToSP(gunList[i]);
	//}

}

void convertAllSPGuns()
{
	//string gunList[] = { "ak47", "m16_basic", "g3", "g36c", "mp5", "skorpion", "uzi", "ak74u", "p90", "saw", "rpd", "m60e4", "m1014", "winchester1200", "m40a3", "remington700", "dragunov", "beretta", "usp", "colt45", "deserteagle" };
}

int main(int argc, char *argv[]){

	if (argc <= 1)
	{
		cout << "Drag and drop some files lol" << endl;
		system("pause");
		return 0;
	}
	
	for (int i = 1; i < argc; i++) {

		string draggedFilePath = argv[i];

		int lastback = draggedFilePath.find_last_of("\\");

		string weaponname = draggedFilePath.substr(lastback + 1, draggedFilePath.length() - lastback + 1);
		cout << draggedFilePath << endl;
		cout << weaponname << endl;

		convertToSP(argv, weaponname,i);

	}


	system("pause");
	//convertAllMPGuns();

//	
//	while (con)
//	{
//		bool chosen = false;
//		//cout << "Command list:" << endl;
//		//cout << "1. Enter filename" << endl;
//		//cout << "2. Convert file to SP" << endl;
//		//cout << "3. Convert file to MP" << endl;
//		//string gunList[] = { "ak47", "m16_basic", "g3", "g36c", "mp5", "skorpion", "uzi", "ak74u", "p90", "saw", "rpd", "m60e4", "m1014", "winchester1200", "m40a3", "remington700", "dragunov", "beretta", "usp", "colt45", "deserteagle" };
//		//string gunList[] = { "ak47_mp", "m16_mp", "g3_mp", "g36c_mp", "mp5_mp", "skorpion_mp", "uzi_mp", "ak74u_mp", "p90_mp", "saw_mp", "rpd_mp", "m60e4_mp", "m1014_mp", "winchester1200_mp", "m40a3_mp", "remington700_mp", "dragunov_mp", "beretta_mp", "usp_mp", "colt45_mp", "deserteagle_mp" };
//		//char mode;
//		//mode = '3';
//		//bool invalid = false;
//		//while (!chosen || (mode != '1' && mode != '2' && fileName != "q")){
//		//	if (!invalid){
//		//		cout << "Select a mode : " << endl << endl;
//		//		cout << "1.SP to MP" << endl;
//		//		cout << "2.MP to SP" << endl << endl;
//		//		cin >> mode;
//		//	}
//		//	else{
//		//		cout << "invalid choice" << endl;
//		//		cin >> mode;
//		//	}
//
//		//	if (mode != '1' && mode != '2')
//		//		invalid = true;
//		//	else
//		//		chosen = true;
//
//		//}
//		bool fvalid = true;
//		fileName = "";
//		while (!fileValid(fileName) && fileName !="q"){
//			if (fvalid)
//				cout << "Input filename" << endl;
//				cin >> fileName;
//			if (!fileValid(fileName) && fileName != "q"){
//				fvalid = false;
//				cout << fileName << " doesn't exist :(" << endl << endl;
//			}
//		}
//		if (fileName == "q"){
//			con = 0;
//		}
//
//		char response;
//
//		if (con){
//			//cout << "Is this a custom weapon? y/n" << endl << endl;
//			//cin >> response;
//			////convertToMP(fileName);
//
//			////for (int i = 0; i < 21; i++)
//			////{
//			//if (response == 'y'){
//			//	customWeapon = true;
//			//	cout << "Custom weapon" << endl << endl;
//			//}
//
//			//if (mode == '1')
//			//	convertToMP(fileName);
//			//if (mode == '2')
//
//		}
//	}
//		
//		/*
//		switch (choice)
//		{
//		case 1:
//		cout << "Input filename" << endl;
//		cin >> fileName;
//		case 2:
//		if (fileName != "")
//		convertToSP(fileName);
//		else
//		cout << "you need a filename" << endl;
//		case 3:
//		if (fileName != "")
//		convertToMP(fileName);
//		else
//		cout << "you need a filename" << endl;
//		case 4:
//		break;
//		}
//*/
//		

}




/*
bool valid(string stringy)
{
	for (int i = 0; i < stringy.length(); i++)
	{
		if (!((stringy.at(i) >= '0' && stringy.at(i) <= '9')))
		{
			//printf("\nIllegal char at %d \n", i);
			return false;
		}
	}
	return true;
}

int factor(int n){
	for (int i = 2; i*i <= n; i++)
	{
		if (n % i == 0) return i;
	}
	return n;
}

void print(vector<int> v, ostream &out = cout){
	for (int i = 0; i < v.size(); i++)
	{
		if (i != (v.size() - 1))
			printf("%2d * ", v[i]);
		else
			printf("%2d ", v[i]);
	}
	cout << endl;


}


vector<int> fact(int n){ //generalized array
	vector<int>  v;
	int f;
	while (true){
		f = factor(n);
		v.push_back(f);

		if (f == n){
			return v;
		}
		n = n / f;
	}

}

int main(){
	ofstream out;
	ifstream in;
	string filename;
	string response;
	bool log;

	cout << "Keep a log? (y/n)" << endl;

	cin >> response;

	if (response.at(0) == 'y'){
		log = true;

		cout << "Enter file name" << endl;

		cin >> filename;

		filename.append(".txt");

		out.open(filename, ios::out | ios::app);
	}
	else
		log = false;

	string n;
	vector<int> v;

	cout << endl;

	while (true) {
		cout << "Enter a number " << endl;
		cin >> n;
		if (!(valid(n)))
		{
			cout << n << " isn't a valid number." << endl;
			cout << endl;
			continue;
		}

		if (atoi(n.c_str()) < 2)
		{
			cout << endl;
			cout << "Terminating..." << endl;
			out.close();
			break;
		}

		int number = atoi(n.c_str());

		v = fact(number);
		if (v.size() == 1){
			cout << endl;
			printf("%d is a prime!\n", number);
			printf("\n");
			if (log){
				out << number << " is a prime number!" << endl;
				out << endl;
			}
		}
		else{
			printf("\n");
			printf("%d =", number);
			print(v, out);
			printf("\n");
			if (log){
				out << number << " = ";
				for (int i = 0; i < v.size(); i++)
				{
					if (i != (v.size() - 1)){
						out << v[i] << " * ";
						//printf("%2d * ", v[i]);
					}
					else{
						out << v[i];
						//printf("%2d ", v[i]);
					}
				}
				out << endl;
				out << endl;
			}


		}
	}
}
*/