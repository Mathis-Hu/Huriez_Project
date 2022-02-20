/**
 * Cette classe gère les différentes fenêtres du jeu
 *
 * @author Mathis HURIEZ & Hugo DESCROIX
 */


import javax.swing.*;
import java.awt.*;


public class Frame extends JFrame
{
    /** Attribut qui correspond à la fenêtre utilisée */
	private final JFrame frame;

    /** Constructeur qui initialise la fenêtre */
	public Frame()
    {
		this.frame = new JFrame();
	}
    

    /** Méthode qui permet de créer la fenêtre de menu */
	public void menu()
    {
        Buttons button;
        
        Frame game = new Frame();

        this.frame.setSize(450, 250);
        this.frame.setLocation(100, 100);
        this.frame.setTitle("Menu");
        this.frame.setResizable(false);
        this.frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        GridLayout align = new GridLayout(3, 1);
        this.frame.setLayout(align);

        JLabel title = new JLabel("SameGame");
        title.setFont(new Font("Verdana", Font.ITALIC, 50));
        title.setVerticalAlignment(JLabel.CENTER);
        title.setHorizontalAlignment(JLabel.CENTER);
        this.frame.add(title);

        JPanel panel = new JPanel();
        FlowLayout layout = new FlowLayout(FlowLayout.CENTER);
        panel.setLayout(layout);

        /** Permet de lancer une partie */
        game.frame();

        /** Boutons du menu */
        button = new Buttons(game.frame, frame);

        JButton level = new JButton("Choisissez un niveau");
        JButton random = new JButton("Génération aléatoire");
        JButton quit = new JButton("Quitter");

        quit.setBackground(Color.RED);

        /** Ajout des boutons */
        panel.add(level);
        level.addActionListener(button);
        panel.add(random);
        random.addActionListener(button);
        panel.add(quit);
        quit.addActionListener(button);

        this.frame.add(panel);

        JLabel credit = new JLabel("Par Hugo Descroix et Mathis Huriez");
        credit.setFont(new Font("Verdana", Font.ITALIC, 20));
        credit.setVerticalAlignment(JLabel.BOTTOM);
        credit.setHorizontalAlignment(JLabel.CENTER);
        this.frame.add(credit);

        this.frame.setVisible(true);
    }


    /** Méthode qui créer une fenêtre de jeu */
     private void frame()
     {
        this.frame.setSize(755, 600);
        this.frame.setLocation(100, 100);
        this.frame.setResizable(false);
        this.frame.setTitle("SameGame");
        this.frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel location = new JPanel();
        JPanel score = new JPanel();

        this.frame.add(location);
        this.frame.add(score);
        this.frame.add(score, BorderLayout.SOUTH);
    }


    /** Méthode qui gère les fenêtres en fin de partie */
    public static void end(JFrame window, JFrame menu, int score)
    {
        JButton back = new JButton("Menu");
        JButton quit = new JButton("Quitter");
        Buttons endGame = new Buttons(menu, window);
        String str;
        window.getContentPane().removeAll();
        window.getContentPane().revalidate();
        window.setSize(450, 250);

        str = "Votre score est de " + score;
        
        JLabel title = new JLabel(str);
        title.setVerticalAlignment(JLabel.CENTER);
        title.setHorizontalAlignment(JLabel.CENTER);
        window.add(title);

        GridLayout align = new GridLayout(3, 1);
        window.setLayout(align);

        JPanel panel = new JPanel();
        FlowLayout layout = new FlowLayout(FlowLayout.CENTER);
        panel.setLayout(layout);

        quit.setBackground(Color.RED);
        panel.add(back);
        panel.add(quit);
        window.add(panel);
        quit.addActionListener(endGame);
        back.addActionListener(endGame);
        window.getContentPane().repaint();
    }
}