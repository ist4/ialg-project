namespace Binary
{
  const string BINARY_FILENAME = "medicines.bin";

  void writeMedicines(Medicine medicines[], int size)
  {
    ofstream outfile(BINARY_FILENAME, ios::binary | ios::out | ios::trunc);
    if (outfile.is_open())
    {
      outfile.seekp(0, ios::beg);
      outfile.write(reinterpret_cast<char *>(medicines), sizeof(Medicine) * size);
      outfile.close();
    }
    else
    {
      cerr << "Erro: Não foi possível abrir o arquivo binário para escrita." << endl;
    }
  };

  size_t getMedicineFileSize(ifstream &file, int &numberOfElements)
  {
    file.seekg(0, ios::end);
    size_t fileSize = file.tellg();
    size_t elementSize = sizeof(Medicine);

    numberOfElements = fileSize / elementSize;

    return fileSize;
  }

  void displayMedicines()
  {
    ifstream binfile(BINARY_FILENAME, ios::in | ios::binary);
    if (binfile.is_open())
    {
      // getting the filesize
      int numberOfMedicines;
      size_t fileSize = getMedicineFileSize(binfile, numberOfMedicines);
      Medicine medicinesRead[numberOfMedicines];

      binfile.seekg(0, ios::beg);

      binfile.read(reinterpret_cast<char *>(&medicinesRead), fileSize);
      binfile.close();

      for (int i = 0; i < numberOfMedicines; i++)
      {
        cout << medicinesRead[i].id << " " << medicinesRead[i].value << " " << medicinesRead[i].pricesAreTheSame << " " << medicinesRead[i].description << " " << medicinesRead[i].marketPrice << endl;
      }
    }
    else
    {
      cerr << "Erro: Não foi possível abrir o arquivo binário para leitura." << endl;
    }
  };

  // number of medicines is passed by reference
  // if the file is not found, the number of medicines is set to 0
  Medicine *getAllMedicines(int &numberOfMedicines)
  {
    ifstream binfile(BINARY_FILENAME, ios::in | ios::binary);
    if (binfile.is_open())
    {
      // getting the number of medicines by reference
      getMedicineFileSize(binfile, numberOfMedicines);
      Medicine *medicinesRead = new Medicine[numberOfMedicines];

      for (int i = 0; i < numberOfMedicines; i++)
      {
        binfile.seekg(i * sizeof(Medicine), ios::beg);
        binfile.read(reinterpret_cast<char *>(&*(medicinesRead + i)), sizeof(Medicine));
      }

      binfile.close();

      return medicinesRead;
    }
    else
    {
      cerr << "Erro: Não foi possível abrir o arquivo binário para leitura." << endl;
      binfile.close();
      numberOfMedicines = 0;
      Medicine *invalidMedicinePtr = new Medicine[numberOfMedicines];
      return invalidMedicinePtr;
    }
  };

  bool completelyRemoveMedicineFromFile(fstream &fileMedicine, Medicine *med)
  {
    // TODO implement
    return true;
  }
}
