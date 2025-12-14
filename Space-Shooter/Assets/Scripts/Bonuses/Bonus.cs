using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bonus : MonoBehaviour
{
    public string type;
    
    public float speed = 5;
    public float threshold = -10;

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
