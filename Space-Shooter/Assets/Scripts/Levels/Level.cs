using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Level : MonoBehaviour
{
    public GameObject[] enemyTypes;
    protected List<(int type, float x, float time)> enemies;
    protected float timer;
    protected int enemyCounter;
    protected Player player;
    
    protected bool paused = false;

    public void Pause()
    {
        paused = true;
    }

    public void Unpause()
    {
        paused = false;
    }
}
