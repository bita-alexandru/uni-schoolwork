using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PopupText : Pausable
{
    // Start is called before the first frame update
    float displayTime;
    string effect;
    string message;
    
    Player player;

    TextMesh text;

    float timer = 0f;

    void Awake()
    {
        player = FindObjectOfType<Player>();

        text = GetComponent<TextMesh>();
    }

    // Update is called once per frame
    void Update()
    {
        if (paused) return;

        if (!player)
        {
            Destroy(this.gameObject);
            return;
        }

        ApplyEffect();
    }

    void ApplyEffect()
    {
        if (effect == "FADE OUT")
        {
            if (timer >= displayTime)
            {
                float fadoutSpeed = 3f;
                text.color -= new Color(0f, 0f, 0f, fadoutSpeed*Time.deltaTime);
                
                if (text.color.a <= 0.0f)
                {
                    Destroy(this.gameObject);
                    return;
                }

                return;
            }
        }

        timer += Time.deltaTime;
    }

    public void Setup(string message, string effect, float displayTime)
    {
        this.message = message;
        this.effect = effect;
        this.displayTime = displayTime;

        if (effect == "FADE OUT")
        {
            text.text = message;
        }
    }

    public void SetColor(Color color)
    {
        text.color = color;
    }

}
