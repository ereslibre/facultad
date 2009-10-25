package color;

import java.util.ArrayList;
import processing.core.*;

public class Main extends PApplet {

    class Punto {
        public float x;
        public float y;
    }

    ArrayList<Punto> mesas = new ArrayList<Punto>();

    public Main() {
    }

    public static void main(String[] args) {
        PApplet.main(new String[]{"color.Main"});
    }

    @Override
    public void setup() {
        size(480, 480);
        smooth();
        for (int i = 0; i < 10; ++i) {
            Punto p = new Punto();
            p.x = (float) (Math.random() * 480);
            p.y = (float) (Math.random() * 360 + 120);
            mesas.add(p);
        }
    }

    @Override
    public void draw() {
        background(255);
        noFill();
        stroke(0);
        arc(240, 0, 480, 240, 0, PI);
        noStroke();
        fill(color(0, 0, 0, 0));
        rect(240 - 20 / 2, 40, 20, 20);
        {
            for (int i = 0; i < 10; ++i) {
                final Punto p = mesas.get(i);
                arc(p.x, p.y, 20, 20, 0, TWO_PI);
            }
        }
    }

}
