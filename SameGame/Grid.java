/**
* La classe Grid est utilisée pour générer une grille de jeu
* 
* @author Mathis HURIEZ & Hugo DESCROIX
*/


import javax.swing.JComponent;
import javax.swing.*;
import java.awt.*;
import java.util.Random;
import java.io.FileReader;
import java.io.Reader;
import java.io.File;
import java.io.IOException;
import java.io.FileNotFoundException; 
import java.io.BufferedReader;


public class Grid extends JComponent 
{
  /** Tableau représentant la valeur des cases de la grille lors de l'initialisation */
  private int[][] tabgrid;

  /** Tableau représentant la valeur des cases de la grille lors du jeu */
  private int[][] copy;

  /** Tableau représentant la couleur des cases de la grille lors de la lecture d'un fichier (R pour rouge, V pour vert et B pour bleu) */
  private char[][] character;

  /** Tableau symbolisant la surbrillance des blocs dans la grille (true si la case est en surbrillance, false sinon) */
  private boolean[][] selected;

  /** Tableau contenant toutes les images nécessaires au jeu */
  private Image[] loadPicturesTab;

  /** Indice du déroulement de la partie (vaut 0 lors de l'initialisation de la partie, vaut 1 pendant la partie) */
  private int inGame;

  /** Indice représentant le choix du joueur (0 pour une génération aléatoire, 1 pour une lecture de fichier) */
  private int mode;

  /** Variable contenant le score du joueur au cours de la partie */
  private double score;


  /**
  * Constructeur destiné à la génération d'une grille en mode aléatoire
  */
  public Grid(int choice) 
  {
    super();
    this.tabgrid = new int[15][10];
    this.selected = new boolean[15][10];
    this.copy = new int[15][10];
    this.mode = choice;
    this.inGame = 0;
    this.score = 0;
  
    for(int j = 0 ; j < 15; j++)
    {
      for(int i = 0; i < 10; i++)
      {
        this.selected[j][i] = false;
      }
    }

    this.setPreferredSize(new Dimension(500,500));
    this.loadPicturesTab = new Image[7];

    for (int i = 0; i < 7; i++)
    {
      this.loadPicturesTab[i] = Toolkit.getDefaultToolkit().getImage("token/"+ i +".png");
    }
  }


  /**
  * Constructeur destiné à la génération d'une grille en mode lecture
  */
  public Grid(int choice, File file)
  {
    super();
    this.tabgrid = new int[15][10];
    this.selected = new boolean[15][10];
    this.character = new char[15][10];
    this.copy = new int[15][10];
    this.mode = choice;
    this.inGame = 0;
    this.score = 0;
    String line;
  
    for(int j = 0 ; j < 15; j++)
    {
      for(int i = 0; i < 10; i++)
      {
        this.selected[j][i] = false;
      }
    }
  
    try
    {
      FileReader f = new FileReader(file);
      BufferedReader ligne = new BufferedReader(f);
     
      try
      {
        for( int i = 0; i < 10; i++)
        {
          line = ligne.readLine();
        
          for (int j = 0; j < 15; j++) 
          {
            this.character[j][i] = line.charAt(j);
          }
        }
      }

      catch(FileNotFoundException fileE)
      {
        System.out.println("Il y a un problème avec la lecture.");
      }

      f.close();
    }

    catch(IOException ioE)
    {
      System.out.println("Il y a un problème avec le read.");
    }

    this.setPreferredSize(new Dimension(50,50));
    this.loadPicturesTab = new Image[7];
    
    for (int i = 0; i < 7; i++) 
    {
      this.loadPicturesTab[i] = Toolkit.getDefaultToolkit().getImage("token/"+ i +".png");
    }
  }


  /**
  * Renvoie la valeur de sélection de la case
  */
  public boolean getSelected(int x, int y)
  {
    return this.selected[x][y];
  }


  /**
  * Définie une valeur dans le tableau selected
  */
  public void setSelected(int x, int y, boolean bool)
  {
    this.selected[x][y] = bool;
  }


  /**
  * Renvoie la valeur de la case
  */
  public int getBoxValue(int x, int y)
  {
    return this.tabgrid[x][y];
  }


  /**
  * Définie une nouvelle valeur pour la case.
  */
  public void setBoxValue(int x, int y, int value)
  {
    this.tabgrid[x][y] = value;
  }


  /**
  * Définie une nouvelle valeur pour la case dans la copie
  */
  public void setBoxCopyValue(int x , int y,int value) 
  {
    this.copy[x][y] = value;
  }


  /**
  * Modifie le score en fonction du nombre de blocs éliminés
  */
  public void setScore(double count)
  {
    this.score = this.score + Math.pow((count -2),2);
  }


  /** Renvoie la valeur de la case */
  public int getScore()
  {
    return (int)this.score;
  }
  

  /**
  * Génère la surbrillance du groupe survolé par la souris
  */
  public void checkBlock(int posX, int posY) 
  {
    int tmp_img;
    
    try
    {
      this.setSelected(posX, posY, true);
      
      if (posX > 0) 
      {
        if (this.tabgrid[posX][posY] == this.tabgrid[posX-1][posY] && this.selected[posX-1][posY] == false) 
        {
          this.checkBlock(posX-1,posY);
        }
      }

      if (posY > 0) 
      {
        if (this.tabgrid[posX][posY] == this.tabgrid[posX][posY-1] && this.selected[posX][posY-1] == false) 
        {
          this.checkBlock(posX,posY-1);
        }
      }

      if (posX < 14) 
      {
        if (this.tabgrid[posX][posY] == this.tabgrid[posX+1][posY] && this.selected[posX+1][posY] == false) 
        {
          this.checkBlock(posX+1,posY);
        }
      }

      if (posY < 9) 
      {
        if (this.tabgrid[posX][posY] == this.tabgrid[posX][posY+1] && this.selected[posX][posY+1] == false) 
        {
          this.checkBlock(posX,posY+1);
        }
      }

      tmp_img = this.tabgrid[posX][posY] + 4;
      this.setBoxValue(posX, posY, tmp_img);
    }

    catch(ArrayIndexOutOfBoundsException e){}
  }


  /** Renvoie le nombre de blocs séléctionés */
  public double countSelected() 
  {
    double count = 0;
  
    for(int j = 0 ; j < 15; j++)
    {
      for(int i = 0; i < 10; i++)
      {
        if(this.selected[j][i]) 
        {
          count++;
        }
      }
    }
    
    return count;
  }


  /** Remet les anciennes cases séléctionées à l'état initial */
  public void erasingSelection() 
  {
    for(int j = 0 ; j < 15; j++)
    {
      for(int i = 0; i < 10; i++)
      {
        this.selected[j][i] = false;
        this.tabgrid[j][i] = this.copy[j][i];
      }
    }
  }


  /**
  * Affiche la grille et le score dans la fenêtre
  */
  @Override
  public void paintComponent(Graphics pinceau) 
  {
    Graphics secondPinceau = pinceau.create();
    Random composant = new Random();

    if(this.inGame == 0)
    {
      for (int j = 0; j < 10; j++) 
      {
        for (int k = 0; k < 15; k++) 
        {
          if(this.mode == 0)
          {
            this.tabgrid[k][j] = composant.nextInt(3);

            if (this.tabgrid[k][j] == 0) 
            {
              secondPinceau.drawImage(this.loadPicturesTab[0],k*50,j*50, this);
            }

            else if (this.tabgrid[k][j] == 1) 
            { 
              secondPinceau.drawImage(this.loadPicturesTab[1],k*50,j*50, this);
            }

            else 
            {
              secondPinceau.drawImage(this.loadPicturesTab[2],k*50,j*50,this);
            }

            this.copy[k][j]=this.tabgrid[k][j]; 
          }

          else
          {
            if (this.character[k][j] == 'R') 
            {
              this.tabgrid[k][j] = 0;
              secondPinceau.drawImage(this.loadPicturesTab[0],k*50,j*50, this);
            }

            else if (this.character[k][j] == 'V') 
            {
              this.tabgrid[k][j] = 1;
              secondPinceau.drawImage(this.loadPicturesTab[1],k*50,j*50, this);
            }
 
            else if(this.character[k][j] == 'B') 
            {
              this.tabgrid[k][j] = 2;
              secondPinceau.drawImage(this.loadPicturesTab[2],k*50,j*50,this);
            }

            this.copy[k][j]=this.tabgrid[k][j]; 
          }
        }  
      }
    }
  
    if (this.inGame == 1) 
    {
      for (int i = 0; i < 10; i++) 
      {
        for (int l = 0; l < 15; l ++) 
        {
          switch(getBoxValue(l,i)) 
          {
            case 0:
              secondPinceau.drawImage(this.loadPicturesTab[0],l*50,i*50, this);
              break;
    
            case 1:
              secondPinceau.drawImage(this.loadPicturesTab[1],l*50,i*50, this);
              break;

            case 2:
              secondPinceau.drawImage(this.loadPicturesTab[2],l*50,i*50, this);
              break;

            case 3:
              break;
  
            case 4:
              secondPinceau.drawImage(this.loadPicturesTab[4],l*50,i*50, this);
              break;
    
            case 5:
              secondPinceau.drawImage(this.loadPicturesTab[5],l*50,i*50, this);
              break;
    
            case 6:
              secondPinceau.drawImage(this.loadPicturesTab[6],l*50,i*50, this);
              break;

            case 7:
              break;
          }
        }
      }
    }

    this.inGame = 1;
    secondPinceau.setFont(new Font("default", Font.BOLD, 18));
    secondPinceau.drawString("Score: "+(int)this.score, 350, 550);
  }
}