/**
*   La classe Mouse est utilisée pour gérer les différents mouvements de la souris 
*
* @author Mathis HURIEZ & Hugo DESCROIX
*/

import javax.swing.*;
import java.awt.event.*;
import java.lang.Object;


public class Mouse implements MouseMotionListener, MouseListener 
{
	/** Attribut privé de l'abscisse de la souris */
	private int mouseXPos;

    /** Attribut privé de l'ordonné de la souris */
	private int mouseYPos;

    /** Attribut privé qui permet de récupérer les informations de la grille */
	private Grid grid;

    /** Attribut privé qui permet de récupérer la fenêtre de jeu */
    private JFrame wind;

    /** Attribut privé qui permet de récupérer la fenếtre de menu */
    private JFrame windclose;


    /**
    * Constructeur destiné à la création des constantes publiques et l'initialisation de l'abscisse et l'ordonné de la souris
    */
	public Mouse(Grid gd, JFrame window, JFrame windclose) 
    {
		this.wind = window;
        this.windclose = windclose;
		this.mouseXPos = 0;
		this.mouseYPos = 0;
		this.grid = gd;
	}


    /** Lors d'un clic, on supprime les blocs de la grille si c'est possible puis on décale les blocs */
    @Override
    public void mouseClicked(MouseEvent event) 
    {
    	Movement move = new Movement(this.grid);
        int score;

        if((this.grid.countSelected() > 1) && (this.grid.getBoxValue(this.mouseXPos,this.mouseYPos) != 3) && (this.grid.getBoxValue(this.mouseXPos,this.mouseYPos) != 7))
        {
        	move.deletingBlock();
        	this.grid.setScore(this.grid.countSelected());
        }

        move.bottomMove();
        move.leftMove();

        this.grid.repaint();

        if(move.gameOver())
        {
            score = this.grid.getScore();
            Frame.end(this.wind, this.windclose, score);
        }

        this.mouseMoved(event);
    }

   
    @Override
    public void mouseDragged(MouseEvent event) {}


    @Override
    public void mouseEntered(MouseEvent event) {}          


    /** Méthode qui enlève la sélection lors d'une sortie de fenêtre */
    @Override
    public void mouseExited(MouseEvent event) 
    {
        this.grid.erasingSelection();
    }


    /** Méthode qui vérifie si il y a possibilité de grouper les blocs */
    @Override
    public void mouseMoved(MouseEvent event) 
    {
    	this.grid.erasingSelection();
    	this.mouseXPos = (int)(event.getX()/50);
    	this.mouseYPos = (int)(event.getY()/50);
    	this.grid.checkBlock(this.mouseXPos,this.mouseYPos);
    	this.grid.repaint();
    	this.grid.countSelected();
    }


    @Override
    public void mousePressed(MouseEvent event) {}

    
    @Override
    public void mouseReleased(MouseEvent event) {}
}