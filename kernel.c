void print(const char* str) {
    unsigned short* video_memory = (unsigned short*)0xB8000;

    for (int i = 0; str[i] != '\0'; ++i) {
        video_memory[i] = (video_memory[i] & 0xFF00) | str[i];
    }
}

void kernel_main() {
    print("Welcome to LuminosityOS!");
    print("-------------------------");
    print("We are going to install system files...");
    //code will go here
    print("Installation has finished, awaiting boot into graphics mode");
    print("While you wait, here is my 'thanks you's!");
    print("Thanks to KolibriOS and its devs for inspiration");
    print("Thanks to my friends for being supportive");
    print("And thank you for making this possible ;)");
    
    while(1) {
    }
}  
