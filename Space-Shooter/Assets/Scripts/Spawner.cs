using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spawner : MonoBehaviour
{
    public GameObject[] enemies;
    public GameObject[] levels;
    public GameObject _level;
    public float cooldown;

    float timer;
    // Start is called before the first frame update
    void Start()
    {
        timer = 0;
    }

    // Update is called once per frame
    void Update()
    {
        //Spawn();
    }

    void Spawn()
    {
        if (timer >= cooldown)
        {
            /*int type = Random.Range(0, enemies.Length);
            GameObject enemy = enemies[type];

            float x = Random.Range(-5, 5);
            float y = 7;

            Vector3 position = new Vector3(x, y);

            GameObject _enemy = Instantiate(enemy);
            _enemy.GetComponent<Transform>().position = position;
               */
            //Missile missileCopy = Instantiate<Missile>(missile);
            /*GameObject level = levels[0];
            _level = Instantiate(level);*/
            timer = 0;
        }
        else
        {
            timer += Time.deltaTime;
        }
    }
}
