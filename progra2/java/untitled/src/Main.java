import java.util.ArrayList;


public class Main {
    public static void main(String[] args) {
        ArrayList <String> comidas = new ArrayList<String>();

        comidas.add ("chaufa");
        comidas.add ("gallina");
        comidas.add ("dsa");
        ArrayList <String> prueba = new ArrayList <String> (comidas);

        for (String it : prueba) {
            System.out.println(it);
        }

        System.out.println(prueba.size());

            for (String it : comidas) {
            System.out.println (it);
        }
        Persona persona = new Persona();
        persona.asignar(persona);
        persona.setDni(156);
        persona.setNombre("Paola");
        persona.setSueldo(321.323);

        Persona perro = new Persona(persona);
        System.out.println(perro.getNombre());
        System.out.println(perro.getSueldo());
        System.out.println(perro.getDni());
    }
}