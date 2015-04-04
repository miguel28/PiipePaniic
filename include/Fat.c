void ReadFAT(){
    FILE* testRead1 = fopen ("PiipePaniic.dat", "rb");
	if(testRead1==NULL)WriteFAT();
	else fread(&FatSlot, 1, sizeof(FatSlot), testRead1);
	fclose(testRead1);
}
void WriteFAT(){
    FILE* testRead1 = fopen ("PiipePaniic.dat", "wb");
	fwrite(&FatSlot, 1, sizeof(FatSlot), testRead1);
	fclose(testRead1);
}
