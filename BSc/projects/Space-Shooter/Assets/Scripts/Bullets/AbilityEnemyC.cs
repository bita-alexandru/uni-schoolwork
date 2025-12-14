using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AbilityEnemyC : Ability
{
    public float speed = 3;
    public int damage = 2;
    public int segments=50;
    private bool abilityMov = true;
    private float timer;
    private float penaltyTime = 3;
    float threshold = -10f;
    LineRenderer line;

    // Start is called before the first frame update
    void Start()
    {
        effect = "ROOT";
        duration = 3;

        player = FindObjectOfType<Player>();
        line = gameObject.GetComponent<LineRenderer>();
        line.positionCount = segments + 1;

        timer = 0;
    }

    // Update is called once per frame
    void Update()
    {
        if (!player)
        {
            Destroy(this.gameObject);
        }

        if (transform.position.y < threshold)
        {
            Destroy(this.gameObject);
        }
        
        float x;
        float y;

        float radius = 1.5f;
        float angle = 20f;
        for (int point = 0; point < segments + 1; point++)
        {
            x = transform.position.x + Mathf.Cos(Mathf.Deg2Rad * angle) * radius;
            y = transform.position.y + Mathf.Sin(Mathf.Deg2Rad * angle) * radius;

            line.SetPosition(point, new Vector3(x, y, 0));

            angle += (360f / segments);
        }
        if (abilityMov == true)
        {
            Vector3 movement = new Vector3(0, speed * Time.deltaTime);
            transform.Translate(movement);
        }
        if(abilityMov == false)
        {
            if (timer >= penaltyTime)
            {
                Destroy(this.gameObject);
            }
            timer = timer + Time.deltaTime;
        }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.CompareTag("PlayerShip"))
        {
            abilityMov = false;
        }
    }
}
