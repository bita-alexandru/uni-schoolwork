using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Level2 : Level
{
    // Start is called before the first frame update
    void Start()
    {
        player = FindObjectOfType<Player>().GetComponent<Player>();

        enemyCounter = InitialiseEnemies();
        player.SetEnemyCounter(enemyCounter);

        timer = 0;
    }

    // Update is called once per frame
    void Update()
    {
        if (paused) return;
        
        if (enemies.Count == 0 || !player)
        {
            Destroy(this.gameObject);
            return;
        }

        for (int i = 0; i < enemies.Count; i++)
        {
            float time = enemies[i].time;

            if (timer >= time)
            {
                int type = enemies[i].type;
                float x = enemies[i].x;

                SpawnEnemy(type, x);

                enemies.RemoveAt(i);
                break;
            }
        }

        timer += Time.deltaTime;
    }

    int InitialiseEnemies()
    {
        enemies = new List<(int type, float x, float time)>();
        // Construieste lista de tuple [inamic, pozitie, timp]
        AddEnemy(0, -2, 1f);
        AddEnemy(1, 0, 1f);
        AddEnemy(0, 2, 1f);
        AddEnemy(1, -3, 3f);
        AddEnemy(0, 0, 4f);
        AddEnemy(1, 2, 7f);
        AddEnemy(0, 1, 8f);
        AddEnemy(2, 0, 11f);

        return enemies.Count;
    }

    void AddEnemy(int type, float x, float t)
    {
        enemies.Add((type, x, t));
    }

    void SpawnEnemy(int type, float x)
    {
        GameObject enemy = enemyTypes[type];

        float y = 7;

        Vector3 position = new Vector3(x, y);

        GameObject _enemy = Instantiate(enemy);
        _enemy.GetComponent<Transform>().position = position;
    }
}
