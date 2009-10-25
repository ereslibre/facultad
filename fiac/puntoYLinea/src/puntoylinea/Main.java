package puntoylinea;

import processing.core.*;

public class Main extends PApplet {

    public Main() {
    }

    public static void main(String[] args) {
        PApplet.main(new String[]{"puntoylinea.Main"});
    }

    final int anchoPantalla = 480;
    final int altoPantalla = 480;
    PFont fuente;

    @Override
    public void setup() {
        size(anchoPantalla, altoPantalla);
        fuente = loadFont("Univers66.vlw.gz");
        strokeWeight(2);
        smooth();
    }

    float angulo = 0;
    int numAristas = 4;
    int creaArista = 0;
    boolean creaAristas = true;
    final int tamanoObjeto = 300;
    boolean modoNormal = true;

    @Override
    public void draw() {
        background(255);
        textFont(fuente, (float) 18.0);
        text("Haz clic para cambiar el metodo de generacion", 10, 20);
        textFont(fuente, (float) 24.0);
        pushMatrix();
        translate(anchoPantalla / 2, altoPantalla / 2);
        angulo += 0.02;
        rotate(angulo);
        final float anguloPorArista = 2 * PI / numAristas;
        final float tamanoArista;
        if (modoNormal) {
            tamanoArista = 2 * PI * (tamanoObjeto / 2) / numAristas;
        } else {
            tamanoArista = (tamanoObjeto / 2) * cos(anguloPorArista);
        }
        final float xPos = -tamanoArista / 2;
        final float yPos = -tamanoObjeto / 2;
        pushMatrix();
        for (int i = 0; i < numAristas; ++i) {
            line(xPos, yPos, xPos + tamanoArista, yPos);
            rotate(anguloPorArista);
        }
        popMatrix();
        if (creaArista == 30) {
            if (creaAristas && numAristas == 30) {
                creaAristas = false;
            } else if (!creaAristas && numAristas == 4) {
                creaAristas = true;
            } else if (creaAristas) {
                ++numAristas;
            } else {
                --numAristas;
            }
            creaArista = 0;
        } else {
            ++creaArista;
        }
        popMatrix();
        if (creaAristas) {
            fill(0);
            text("Creando aristas", 10, 470);
        } else {
            fill(0);
            text("Eliminando aristas", 10, 470);
        }
        if (mousePressed) {
            modoNormal = !modoNormal;
        }
    }

}
