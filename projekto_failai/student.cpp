#include "student.h"

const int NUM_NAMES = 10;
mVector<string> vardai = { "Jonas", "Petras", "Algis", "Marius", "Gintaras", "Tomas", "Lukas", "Simas", "Gabrielius", "Olegas" };
mVector<string> pavardes = { "Kelmutis", "Kelmutaite", "Dangavicius", "Pieliauskas", "Lukavicius", "Simonavicius", "Skaudavicius", "Juzenas", "Darbavicius", "Stankevicius" };

// Default constructor
Studentas::Studentas() : vardas_(""), pavarde_(""), egzaminas_(0.0) {}

// Constructor with parameters
Studentas::Studentas(const std::string& vardas, const std::string& pavarde, double egzaminas, const mVector<int>& nd)
    : vardas_(vardas), pavarde_(pavarde), egzaminas_(egzaminas), nd_(nd) {}

// Copy assignment operator
Studentas& Studentas::operator=(const Studentas& other) {
    if (this != &other) {
        vardas_ = other.vardas_;
        pavarde_ = other.pavarde_;
        egzaminas_ = other.egzaminas_;
        nd_ = other.nd_;
    }
    return *this;
}

//Copy constructor
Studentas::Studentas(const Studentas& other)
    : vardas_(other.vardas_), pavarde_(other.pavarde_), egzaminas_(other.egzaminas_), nd_(other.nd_) {}

// Move constructor
Studentas::Studentas(Studentas&& other) noexcept
    : vardas_(std::move(other.vardas_)),
    pavarde_(std::move(other.pavarde_)),
    egzaminas_(other.egzaminas_),
    nd_(std::move(other.nd_)) {}

// Move assignment operator
Studentas& Studentas::operator=(Studentas&& other) noexcept {
    if (this != &other) {
        vardas_ = std::move(other.vardas_);
        pavarde_ = std::move(other.pavarde_);
        egzaminas_ = other.egzaminas_;
        nd_ = std::move(other.nd_);
    }
    return *this;
}

Studentas::~Studentas() = default;

// Define the calculateGalutinis method for Studentas
double Studentas::calculateGalutinis() const {
    if (nd_.empty()) {
        return 1; // Return 0 if the list of grades is empty
    }
    else {
        double nd_sum = std::accumulate(nd_.begin(), nd_.end(), 0);
        double vidurkis = nd_sum / nd_.size();
        if (useMedian) {
            return 0.4 * useMediana(nd_) + 0.6 * egzaminas_;
        }
        else {
            return 0.4 * vidurkis + 0.6 * egzaminas_;
        }
    }
}

// the output operator
std::ostream& operator<<(std::ostream& os, const Studentas& student) {
    os << left << setw(15) << student.getPavarde() << left << setw(15) << student.getVardas() << left << setw(15) << fixed << setprecision(2) << student.calculateGalutinis();
    return os;
}

// input operator
std::istream& operator>>(std::istream& is, Studentas& student) {
    string vardas, pavarde;
    is >> vardas >> pavarde;
    student.setVardas(vardas);
    student.setPavarde(pavarde);
    return is;
}

bool isNumber(const string& str) {
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

double useMediana(const mVector<int>& grades) {
    if (grades.empty()) {
        return 0.0; // Return 0 if the list of grades is empty
    }

    mVector<int> sortedGrades = grades;
    sort(sortedGrades.begin(), sortedGrades.end());
    int count = sortedGrades.size();
    if (count >= 2) {
        return (sortedGrades[count / 2 - 1] + sortedGrades[count / 2]) / 2.0;
    }
    else {
        return sortedGrades[0]; // Return the single grade if there's only one element in the list of grades
    }
}

void Ivedimas(mVector<Studentas>& stud, bool randomNames, bool randomGrades, bool studentCount) {
    bool moreStudents = true;
    while (moreStudents) {
        //Zmogus zmogus; // Zmogus (neveikia nes yra abstrakti klase)
        Studentas student;
        if (!randomNames && !studentCount) {
            cout << "Iveskite studento varda ir pavarde: ";
            cin >> student; //input operator
        }
        else {
            int randIndex = rand() % NUM_NAMES;
            student.setVardas(vardai[randIndex]); // Use the student object
            student.setPavarde(pavardes[randIndex]); // Use the student object
        }

        if (randomGrades) {
            int ndCount = rand() % 11;
            mVector<int> nd;
            for (int j = 0; j < ndCount; j++) {
                nd.push_back(rand() % 11);
            }
            student.setNd(nd); // Use the student object
            student.setEgzaminas(rand() % 11); // Use the student object
        }
        else {
            string input;
            do {
                cout << "Kiek pazymiu rezultatu turi " << student.getVardas() << " " << student.getPavarde() << ": ";
                cin >> input;
            } while (!isNumber(input));
            int ndCount = stoi(input);

            mVector<int> nd;
            for (int j = 0; j < ndCount; j++) {
                do {
                    cout << j + 1 << " balas: ";
                    cin >> input;
                } while (!(isNumber(input) && stoi(input) >= 0 && stoi(input) <= 10));
                nd.push_back(stoi(input));
            }
            student.setNd(nd); // Use the student object

            do {
                cout << "Iveskite egzamino rezultata: ";
                cin >> input;
            } while (!(isNumber(input) && stoi(input) >= 0 && stoi(input) <= 10));
            student.setEgzaminas(stoi(input)); // Use the student object
        }

        stud.push_back(std::move(student)); // Use the std::move to avoid a copy

        char moreChoice;
        cout << "Ar norite ivesti dar viena studenta? (Y/N): ";
        cin >> moreChoice;
        moreStudents = (moreChoice == 'Y' || moreChoice == 'y');
    }
}

void Spausdinimas(const mVector<Studentas>& stud, bool Mediana) {
    cout << left << setw(15) << "Pavarde" << left << setw(15) << "Vardas" << left << setw(15) << "Galutinis ";
    if (Mediana) {
        cout << left << setw(15) << "Med.";
    }
    else {
        cout << left << setw(15) << "Vid.";
    }
    cout << endl;
    cout << "--------------------------------------------" << endl;

    for (const auto& student : stud) {
        cout << student << endl; //output operator
    }
}

void sortStudents(mVector<Studentas>& students, const string& sortBy, bool Mediana) {
    if (sortBy == "V" || sortBy == "v") {
        sort(students.begin(), students.end(), [](const Studentas& a, const Studentas& b) {
            return a.getVardas() < b.getVardas();
            });
    }
    else if (sortBy == "P" || sortBy == "p") {
        sort(students.begin(), students.end(), [](const Studentas& a, const Studentas& b) {
            return a.getPavarde() < b.getPavarde();
            });
    }
    else if (sortBy == "G" || sortBy == "g") {
        sort(students.begin(), students.end(), [Mediana](const Studentas& a, const Studentas& b) {
            return a.calculateGalutinis() > b.calculateGalutinis();
        });
    }
    else {
        cout << "Neteisingas rikiavimo pasirinkimas. Vykdomas rikiavimas pagal varda." << endl;
        sort(students.begin(), students.end(), [](const Studentas& a, const Studentas& b) {
            return a.getVardas() < b.getVardas();
            });
    }
}

void Pasirinkimai(mVector<Studentas>& students)
{
    char calcChoice;
    cout << "Pasirinkite skaiciavimo metoda (V - vidurkis, M - mediana): ";
    cin >> calcChoice;
    calcChoice = toupper(calcChoice); // Convert to uppercase to handle both cases

    // Check if the user input is valid
    while (calcChoice != 'V' && calcChoice != 'M') {
        cout << "Neteisingas pasirinkimas. Pasirinkite V arba M: ";
        cin >> calcChoice;
        calcChoice = toupper(calcChoice);
    }

    string sortBy;
    cout << "Pasirinkite, kaip norite surusiuoti studentus (V, P, G, EGZ): ";
    cin >> sortBy;

    bool Mediana = (calcChoice == 'M');
    for (auto& student : students) {
        student.calculateGalutinis();
    }
    sortStudents(students, sortBy, Mediana);
    Spausdinimas(students, Mediana);
}

void Generacija(int Pas) {
    for (int fileIndex = 1000; fileIndex <= 10000000; fileIndex *= 10) {
        // Constructing file name with different index
        string fileName = ".studentaiGENERATED_" + to_string(fileIndex) + ".txt";
        if (Pas == 0)
        {
            ofstream fd(fileName);
            if (!fd) {
                cerr << "Failo kurimo error." << endl;
                return;
            }

            auto startCreate = high_resolution_clock::now();

            fd << "Vardas    Pavarde  ND1  ND2  ND3  ND4  ND5  ND6  ND7  ND8  ND9  ND10  Egzaminas" << endl;

            for (int i = 0; i < fileIndex; i++) {
                fd << fixed << left << "Vardas" << i + 1 << " Pavarde" << i + 1;
                cout << setw(15);
                for (int j = 0; j < 10; j++) {
                    fd << " " << fixed << setw(4) << left << rand() % 11;
                }
                fd << " " << rand() % 11 << endl;
            }

            auto stopCreate = high_resolution_clock::now();
            auto durationCreate = duration_cast<milliseconds>(stopCreate - startCreate);


            fd.flush();
            cout << "File " << fileName << " created." << "\n Execution time: " << durationCreate.count() / 1000.0 << " seconds." << endl;
            fd.close();
        }
        // Split students into two files based on their final grade
        if (Pas == 0 || Pas == 1)
        {
            // Split students into two files based on their final grade
        ifstream inputFile(fileName);
        if (!inputFile) {
            cerr << "Error opening file: " << fileName << endl;
            return;
        }

        ofstream highGradesFile(".galvociai" + to_string(fileIndex) + ".txt");
        ofstream lowGradesFile(".nuskriaustukai" + to_string(fileIndex) + ".txt");

        if (!highGradesFile || !lowGradesFile) {
            cerr << "Error creating output files." << endl;
            return;
        }

        auto startSort = high_resolution_clock::now();

        mVector<Studentas> highGrades;
        mVector<Studentas> lowGrades;
        
        string line;
        getline(inputFile, line); // Skip the header line
        while (getline(inputFile, line)) {
            istringstream iss(line);
            Studentas student;
            string vardas, pavarde;
            iss >> vardas >> pavarde;
            student.setVardas(vardas);
            student.setPavarde(pavarde);
            int grade;
            mVector<int> nd;
            while (iss >> grade) {
                nd.push_back(grade);
            }
            if (!nd.empty()) {
                student.setEgzaminas(nd.back());
                nd.pop_back();
            }
            student.setNd(nd);
            student.calculateGalutinis();
            // Add student to appropriate vector based on final grade
            if (student.calculateGalutinis() >= 5)
            {
                highGrades.push_back(student);
            }
            else{
                lowGrades.push_back(student);
            }
        }
        cout << "Number of high grade students: " << highGrades.size() << endl;
        cout << "Number of low grade students: " << lowGrades.size() << endl;

        auto stopSort = high_resolution_clock::now();

        auto startOutput = high_resolution_clock::now();
        // Write high and low grade students to separate files
        highGradesFile << "Vardas    Pavarde  Galutinis (Vid.)" << endl;
        for (const auto& student : highGrades) {
            double finalGrade = student.calculateGalutinis();
            highGradesFile << setw(15) << student.getVardas() << setw(15) << student.getPavarde() << fixed << setprecision(2) << " " << finalGrade << endl;
        }
        
        lowGradesFile << "Vardas    Pavarde  Galutinis (Vid.)" << endl;
        for (const auto& student : lowGrades) {
            double finalGrade = student.calculateGalutinis();
            lowGradesFile << left << setw(15) << student.getVardas() << left << setw(15) << student.getPavarde() << left << setw(15) << fixed << setprecision(2) << " " << finalGrade << endl;
        }
        auto stopOutput = high_resolution_clock::now();
        auto durationOutput = duration_cast<milliseconds>(stopOutput - startOutput);
        cout << " File " << fileIndex << "  output execution time : " << durationOutput.count() / 1000.0 << " seconds." << endl;
        // Close input and output files
        inputFile.close();
        highGradesFile.close();
        lowGradesFile.close();
        
        auto durationSort = duration_cast<milliseconds>(stopSort - startSort);
        
        cout << " File " << fileIndex << "  sorting execution time : " << durationSort.count() / 1000.0 << " seconds." << endl;
        cout << endl;
        }
        // Seperate students based on their final grade and put the low grade students in a separate file
        if (Pas == 2)
        {
            // Split students into two files based on their final grade
            ifstream inputFile(fileName);
            if (!inputFile) {
                cerr << "Error opening file: " << fileName << endl;
                return;
            }
        
            ofstream lowGradesFile(".nuskriaustukai_" + to_string(fileIndex) + ".txt");
        
            if (!lowGradesFile) {
                cerr << "Error creating output files." << endl;
                return;
            }
        
            auto startSort = high_resolution_clock::now();
        
            mVector<Studentas> lowGrades;
        
            string line;
            getline(inputFile, line); // Skip the header line
            while (getline(inputFile, line)) {
                istringstream iss(line);
                Studentas student;
                string vardas, pavarde;
                iss >> vardas >> pavarde;
                student.setVardas(vardas);
                student.setPavarde(pavarde);
                int grade;
                mVector<int> nd;
                while (iss >> grade) {
                    nd.push_back(grade);
                }
                if (nd.size() > 0) {
                    student.setEgzaminas(nd.back());
                    nd.pop_back();
                }
                student.setNd(nd);
                student.calculateGalutinis();
        
                // Add student to appropriate vector based on final grade
                if (student.calculateGalutinis() <= 5)
                    lowGrades.push_back(student);
            }
            auto stopSort = high_resolution_clock::now();
            auto durationSort = duration_cast<milliseconds>(stopSort - startSort);
        
            auto startOutput = high_resolution_clock::now();
            lowGradesFile << "Vardas    Pavarde  Galutinis (Vid.)" << endl;
            for (const auto& student : lowGrades) {
                double finalGrade = student.calculateGalutinis();
                lowGradesFile << left << setw(15) << student.getVardas() << left << setw(15) << student.getPavarde() << left << setw(15) << fixed << setprecision(2) << " " << finalGrade << endl;
            }
            auto stopOutput = high_resolution_clock::now();
            auto durationOutput = duration_cast<milliseconds>(stopOutput - startOutput);
            cout << " File " << fileIndex << "  output execution time : " << durationOutput.count() / 1000.0 << " seconds." << endl;
            // Close input and output files
            inputFile.close();
            lowGradesFile.close();
        
            cout << " File " << fileIndex << "  sorting execution time : " << durationSort.count() / 1000.0 << " seconds." << endl;
            cout << endl;
        }
        if (Pas == 3)
        {
            auto startread = high_resolution_clock::now();
            ifstream inputFile(fileName);
            if (!inputFile) {
                cerr << "Error opening file: " << fileName << endl;
                return;
            }
            string line;
            getline(inputFile, line); // Skip the header line
            mVector<Studentas> students; // Declare the students list
            while (getline(inputFile, line)) {
                istringstream iss(line);
                Studentas student;
                string vardas, pavarde;
                iss >> vardas >> pavarde;
                student.setVardas(vardas);
                student.setPavarde(pavarde);
                int grade;
                mVector<int> nd;
                while (iss >> grade) {
                    nd.push_back(grade);
                }
                if (nd.size() > 0) {
                    student.setEgzaminas(nd.back());
                    nd.pop_back();
                }
                student.setNd(nd);
                double nd_sum = accumulate(nd.begin(), nd.end(), 0);
                double vidurkis = nd_sum / nd.size();
                student.calculateGalutinis();
                students.push_back(student);
            }   

            auto stopread = high_resolution_clock::now();
            auto durationread = duration_cast<milliseconds>(stopread - startread);
            cout << " File " << fileIndex << "  read execution time : " << durationread.count() / 1000.0 << " seconds." << endl;

            auto startSort = high_resolution_clock::now();
            mVector<Studentas> highGradeStudents;
            mVector<Studentas> lowGradeStudents;
        
            for (auto& student : students) {
                if (student.calculateGalutinis() >= 5.0) {
                    highGradeStudents.push_back(student);
                } else {
                    lowGradeStudents.push_back(student);
                }
            }

            auto stopSort = high_resolution_clock::now();
            auto durationSort = duration_cast<milliseconds>(stopSort - startSort);
            cout << " File " << fileIndex << "  sorting execution time : " << durationSort.count() / 1000.0 << " seconds." << endl;

            auto startOutput = high_resolution_clock::now();
            ofstream highGradesFile(".galvociai_" + to_string(fileIndex) + ".txt");
            ofstream lowGradesFile(".vargsiukai_" + to_string(fileIndex) + ".txt");
        
            // Write high grade students to highGradesFile
            for (auto& student : highGradeStudents) {
                double finalGrade = student.calculateGalutinis();
                highGradesFile << student.getVardas().c_str() << " " << student.getPavarde().c_str() << " " << finalGrade << "\n";
            }
            
            // Write low grade students to lowGradesFile
            for (auto& student : lowGradeStudents) {
                double finalGrade = student.calculateGalutinis();
                lowGradesFile << student.getVardas().c_str() << " " << student.getPavarde().c_str() << " " << finalGrade << "\n";
            }
            highGradesFile.close();
            lowGradesFile.close();

            auto stopOutput = high_resolution_clock::now();
            auto durationOutput = duration_cast<milliseconds>(stopOutput - startOutput);
            cout << " File " << fileIndex << "  output execution time : " << durationOutput.count() / 1000.0 << " seconds." << endl;
            cout << endl;
        }
    }
}

void testVectors()
{
    // Sizes to test
    std::vector<unsigned int> sizes = {10000,100000,1000000,10000000,100000000};

    for (auto sz : sizes) {
        cout << "   Testing with size: " << sz << endl;
        // Start timing for std::vector
        auto start1 = std::chrono::high_resolution_clock::now();
        std::vector<int> v1;
        size_t last_capacity = 0;
        size_t reallocations1 = 0;
        for (int i = 1; i <= sz; ++i) {
            if (v1.capacity() != last_capacity) {
                reallocations1++;
                last_capacity = v1.capacity();
            }            
            v1.push_back(i);
        }
        // End timing for std::vector
        auto end1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff1 = end1 - start1;
        cout << "Time to fill std::vector with " << sz << " elements: " << diff1.count() << " s\n";
        cout << "Number of reallocations for std::vector: " << reallocations1 << "\n";
        cout << endl;

        // Start timing for mVector
        auto start2 = std::chrono::high_resolution_clock::now();
        mVector<int> v2;
        last_capacity = 0;
        size_t reallocations2 = 0;
        for (int i = 1; i <= sz; ++i) {
            if (v2.capacity() != last_capacity) {
                reallocations2++;
                last_capacity = v2.capacity();
            }
            v2.push_back(i);
        }
        // End timing for mVector
        auto end2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff2 = end2 - start2;
        cout << "Time to fill mVector with " << sz << " elements: " << diff2.count() << " s\n";
        cout << "Number of reallocations for mVector: " << reallocations2 << "\n";
        cout << endl;
    }
}
