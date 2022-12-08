
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class App
{    
    public static void main(String[] args) {

        File pasta = new File("F:\\Usuarios\\Leonardo\\Downloads\\programaSRTparaVTT\\SRTforVTT" );
        System.out.println( " pasta.toString() = ");
        File[] pastaComTudo = pasta.listFiles();
        ArrayList<String> listaStr =  new ArrayList<String>();

        for(int i=0;i<pastaComTudo.length;i++){
            if(pastaComTudo[i].getName().contains(".srt")){
                listaStr.add(pastaComTudo[i].getName());
            }
        }

        System.out.println( listaStr.toString()); 
       
    } 

    public static void leitor(String path) throws IOException {
		BufferedReader buffRead = new BufferedReader(new FileReader(path));
		String linha = "";
		while (true) {
			if (linha != null) {
				System.out.println(linha);

			} else
				break;
			linha = buffRead.readLine();
		}
		buffRead.close();
	}

	public static void escritor(String path) throws IOException {
		BufferedWriter buffWrite = new BufferedWriter(new FileWriter(path));
		String linha = "";
		Scanner in = new Scanner(System.in);
		System.out.println("Escreva algo: ");
		linha = in.nextLine();
		buffWrite.append(linha + "\n");
		buffWrite.close();
        in.close();
	
}

}