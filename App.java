
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class App {
    public static void main(String[] args) throws IOException {

        // pegar todos os arquivos srt da pasta
        ArrayList<String> listaConverter = pegaTodosSrt();

       if(listaConverter.isEmpty()){
        System.out.println("Atual diretorio não possuiu arquivo .SRT");
       }else{
        // ciclo de pegar toda a srt e converter para vtt
        for (int i = 0; i < listaConverter.size(); i++) {
            ArrayList<String> capitulo = leitor(listaConverter.get(i)); // tras todo texto a ser convertido
            ArrayList<String> capituloConvertido = construtor(capitulo); //converte o texto 
            escritor(listaConverter.get(i), capituloConvertido); //salva num novo arquivo vtt
        }
         System.out.println("Genio da computação, conversão realizada com sucesso");
       }

       System.out.println("Precione qualquer tecla+enter para sair");
       Scanner in = new Scanner(System.in); 
       in.next();
       
    }

    public static ArrayList<String> pegaTodosSrt() {
        File pasta = new File(System.getProperty("user.dir"));
        File[] pastaComTudo = pasta.listFiles();
        ArrayList<String> listaStr = new ArrayList<String>();

        for (int i = 0; i < pastaComTudo.length; i++) {
            if (pastaComTudo[i].getName().contains(".srt")) {
                listaStr.add(pastaComTudo[i].getName());
            }
        }
        return listaStr;
    }

    public static ArrayList<String> leitor(String path) throws IOException {// path nome do arquivo que vai converter
        ArrayList<String> capitulo = new ArrayList<String>();

        BufferedReader buffRead = new BufferedReader(new FileReader(path));
        String linha = "";
        while (true) {
            if (linha == null)
                break;

            linha = buffRead.readLine();
            if(linha !=null)
                capitulo.add(linha);
        }
        buffRead.close();
        return capitulo;
    }

    public static ArrayList<String> construtor(ArrayList<String> capitulo){
        ArrayList<String> capituloConvertido= new ArrayList<>();
        capituloConvertido.add("WEBVTT"); //padrão no inicio do vtt
        capituloConvertido.add(""); //padrão no inicio do vtt 
        //trato a unica excesao que o for nao pega
        capituloConvertido.add("1");  
        capituloConvertido.add(capitulo.get(1).replaceAll(",", ".")) ; 

        for (int i=2;i<capitulo.size();i++){

            if(capitulo.get(i)!=null && capitulo.get(i-2).isEmpty() ){ //sei que estou numa linha com o tempo
                capituloConvertido.add(capitulo.get(i).replaceAll(",", ".")) ; 
                //System.out.println("aqui2");
            }else{
                capituloConvertido.add(capitulo.get(i));    
            }
        }
        return capituloConvertido;
    }

    public static void escritor(String path, ArrayList<String> capitulo) throws IOException {
        path =  path.replace(".srt", ".vtt"); // mudo o nome do arquivo
        BufferedWriter buffWrite = new BufferedWriter(new FileWriter(path));
        for (int i = 0; i < capitulo.size(); i++) {// percorre todo as linhas capitulo
            buffWrite.append(capitulo.get(i) + "\n");
        }
        buffWrite.close(); // salvo o arquivo novo
    }

}