/**
* La classe Buttons est utilisée pour gérer les boutons du jeu
* 
* @author Mathis HURIEZ & Hugo DESCROIX
*/


import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;


public class Buttons implements ActionListener
{
	/** Attribut stockant la fenêtre à ouvrir */
	private JFrame open;

	/**	Attribut stockant la fenêtre à fermer */
	private JFrame close;

	/** Attribut stockant un objet frame pour les règles */
	private Frame frame;

	/** Attribut stockant la grille de jeu créée */
	private Grid grid;

	/** Attribut stockant le fichier à lire */
	public File file;

	/** Attribut vérifiant si la fenêtre est déjà ouverte */
	private boolean checking;


	/**
	*	Constructeur destiné à l'utilisation des différentes fenêtres du jeu
	*/
	public Buttons(JFrame opening, JFrame closing)
	{
		this.open = opening;
		this.close = closing;
		this.checking = false;
	}


	/**
	*	Méthode qui gère les actions en fonctions des boutons
	*/
	@Override
	public void actionPerformed(ActionEvent e)
	{
		String str = e.getActionCommand();

		if(str.equals("Choisissez un niveau"))
		{
			try
			{
				JFileChooser filechose = new JFileChooser("./level");
				int choice = filechose.showOpenDialog(this.close);

				if(choice == JFileChooser.APPROVE_OPTION)
				{
					file = filechose.getSelectedFile();
				}

				grid = new Grid(1, file);
				this.open.add(grid);

				Mouse action = new Mouse(grid, this.open, this.close);
				grid.addMouseListener(action);
				grid.addMouseMotionListener(action);

				this.close.dispose();
				this.open.setVisible(true);
			}

			catch(NullPointerException npe){}
		}

		if(str.equals("Génération aléatoire"))
		{
			grid = new Grid(0);
			this.open.add(grid);
			this.close.dispose();
			this.open.setVisible(true);
			Mouse action = new Mouse(grid, this.open, this.close);
			grid.addMouseListener(action);
			grid.addMouseMotionListener(action);
		}

		if(str.equals("Quitter"))
		{
			this.close.dispose();
		
			try
			{
				this.open.dispose();
			}

			catch(NullPointerException nor){}
		}

		if(str.equals("Menu"))
		{
			this.close.dispose();
			Frame menu = new Frame();
			menu.menu();
		}
	}
}