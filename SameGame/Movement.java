/**
* La classe Movement est utilisée pour gérer les décalages dans la grille
* 
* @author Mathis HURIEZ & Hugo DESCROIX
*/

public class Movement
{
	private Grid grid;
	private boolean[][] selection;
	private boolean[][] emptyBox;
	private int[][] tabIm;


	/**
	* Constructeur destiné à contenir les informations de la grille
	*/
	public Movement(Grid grid) 
	{		
		this.grid = grid;
		this.selection = new boolean[15][10];
		this.emptyBox = new boolean[15][10];
		this.tabIm = new int[15][10];

		for(int j = 0 ; j < 15 ; j++) 
		{
			for(int i = 0 ; i < 10 ; i++) 
			{
				this.selection[j][i] = this.grid.getSelected(j,i);
				this.tabIm[j][i] = this.grid.getBoxValue(j,i);
			}
		}
	}


	/** Méthode qui prends en compte les informations du tableau pour supprimer les blocs surlignés */
	public void deletingBlock() 
	{
		for(int i = 0 ; i < 15 ; i++) 
		{
			for(int j = 0 ; j < 10 ; j++) 
			{
				if(this.selection[i][j]) 
				{
					this.grid.setBoxValue(i,j,3);
					this.grid.setBoxCopyValue(i,j,3);
					this.tabIm[i][j] = 3;
					this.emptyBox[i][j] = true;
				}
			}
		}
	}


	/** Méthode qui analyse le tableau pour trouver des colonnes vides et décaler la grille à gauche */
	public void leftMove() 
	{
		int tmp;

		for(int i = 0 ; i < 15 ; i++) 
		{
			if((this.tabIm[i][9] == 3) || (this.tabIm[i][9] == 7)) 
			{
				for(int j = 0 ; j < 10 ; j++) 
				{
					if((i < 14) && (i > -1)) 
					{
						if((this.tabIm[i+1][j] != 3) && (this.tabIm[i+1][j] != 7)) 
						{
							this.tabIm[i][j] = this.tabIm[i+1][j];
							this.tabIm[i+1][j] = 3;
							this.grid.setBoxValue(i,j,this.tabIm[i][j]);
							this.grid.setBoxValue(i+1,j,3);
							this.grid.setBoxCopyValue(i,j,this.tabIm[i][j]);
							this.grid.setBoxCopyValue(i+1,j,3);
							i = -1;
						}
					}
				}       
			}
		}
	}


	/** Méthode qui analyse le tableau pour trouver la possibilité de décaler les blocs vers le bas */
	public void bottomMove() 
	{
		int tmp;

		for (int i = 0 ; i < 15 ; i++) 
		{
			for (int j = 0 ; j < 10 ; j++) 
			{
				if((this.tabIm[i][j] == 3) || (this.tabIm[i][j] == 7)) 
				{
					if(j > 0) 
					{
						if((this.tabIm[i][j-1] != 3) && (this.tabIm[i][j-1] != 7)) 
						{
							tmp = this.tabIm[i][j-1];
							this.tabIm[i][j-1] = 3;
							this.tabIm[i][j] = tmp;
							this.grid.setBoxValue(i,j,tmp);
							this.grid.setBoxValue(i,j-1,3);
							this.grid.setBoxCopyValue(i,j,tmp);
							this.grid.setBoxCopyValue(i,j-1,3);
							j = -1;
						}
					}
				}
			}
		}
	}


	/** Retourne true si la partie est finie, sinon false */
    public boolean gameOver() 
    {
        for(int i = 0 ; i < 15 ; i++) 
        {
            for(int j = 0 ; j < 10 ; j++) 
            {
                if(identifyNearColor(i, j))
                {
                    return false;
                }
            }
        }

        return true;
    }


    /**
	*	Méthode qui cherche un bloc de même couleur parmi les cases voisines
	*/
    private boolean identifyNearColor(int i, int j)
    {
        if(grid.getBoxValue(i ,j) != 3 && grid.getBoxValue(i ,j) != 7)
        {
            if(i + 1 < 15 && grid.getBoxValue(i ,j) == grid.getBoxValue(i + 1, j))
            {
                return true;
            }
            
            else if(i - 1 > 0 && grid.getBoxValue(i ,j) == grid.getBoxValue(i - 1, j))
            {
                return true;
            }
            
            else if(j + 1 < 10 && grid.getBoxValue(i ,j) == grid.getBoxValue(i, j + 1))
            {
                return true;
            }

            else if(j - 1 > 0 && grid.getBoxValue(i ,j) == grid.getBoxValue(i, j - 1))
            {
                return true;
            }
        }

        return false;
    }
}